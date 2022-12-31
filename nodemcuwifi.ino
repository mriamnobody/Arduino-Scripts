#include <ESP8266WiFi.h>
int wifi_connection() {
  int numNetworks = WiFi.scanNetworks();

  // Print the number of networks found
  Serial.println("\nNumber of networks found: " + String(numNetworks));

  // Print the details of each network found
  for (int i = 0; i < numNetworks; i++) {
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(WiFi.SSID(i));
    Serial.print(" (");
    Serial.print(WiFi.RSSI(i));
    Serial.print(")");

    // Determine the WiFi band of the AP
    int channel = WiFi.channel(i);
    if (channel == 1 || channel == 2 || channel == 3 || channel == 4 || channel == 5 || channel == 6 || channel == 7 || channel == 8 || channel == 9 || channel == 10 || channel == 11 || channel == 12 || channel == 13) {
      Serial.print(" 2.4 GHz");
    } else {
      Serial.print(" 5 GHz");
    }
    Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
  }

  Serial.println("Enter the number of the network you want to connect to: ");

  // Wait for the user to enter the index of the network
  while (!Serial.available());
  int networkIndex = Serial.readString().toInt();

  // Connect to the selected network
  String ssid = WiFi.SSID(networkIndex - 1);
  Serial.print("Enter the password for ");
  Serial.println(ssid);

  // Wait for the user to enter the password
  while (!Serial.available());
  String password = Serial.readString();

  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(50);
    Serial.print(".");
    if (WiFi.status() == WL_CONNECT_FAILED){
      Serial.print("\nIncorrect password\n");
      return 0;
    } else if (WiFi.status() == WL_CONNECTED){
        Serial.println("");
        Serial.println("WiFi connected");  
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        return 1;
    }
    }
}

void setup() {
  Serial.begin(115200);
  delay(10);
  int wasConnectionSuccessful = wifi_connection();

  while (wasConnectionSuccessful == 0) {
    wasConnectionSuccessful = wifi_connection();
  }
}

void loop() {

}