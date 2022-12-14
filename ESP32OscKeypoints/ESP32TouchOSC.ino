/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266/ESP32

  Example for sending messages from the ESP8266/ESP32 to a remote computer
  The example is sending "hello, osc." to the address "/test".

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#else
#include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <OSCMessage.h>

char ssid[] = "Wired2";          // your network SSID (name)
char pass[] = "12!trout";                    // your network password

WiFiUDP Udp;                                // A UDP instance to let us send and receive packets over UDP
const IPAddress outIp(10,0,0,125);        // remote IP of your computer
const unsigned int outPort = 9999;          // remote port to receive OSC
const unsigned int localPort = 8888;        // local port to listen for OSC packets (actually not used for sending)

void setup() {
    Serial.begin(115200);

    // Connect to WiFi network
    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, pass);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    Serial.println("Starting UDP");
    Udp.begin(localPort);
    Serial.print("Local port: ");
#ifdef ESP32
    Serial.println(localPort);
#else
    Serial.println(Udp.localPort());
#endif

}

void loop() {

   OSCBundle bndl;
   int size;
   
    //receive a bundle
   if( (size = Udp.parsePacket())>0)
   {
//        unsigned int outPort = Udp.remotePort();

        while(size--)
           bndl.fill(Udp.read());

       //This is where I'm stuck. I want to use the incoming message to do some work before I send it back out.

        if(!bndl.hasError())
        {
			//and echo it back
			if(bndl.size() > 0)
			{
				msgIN.route("/keypoints",receiveKeypoints);
			}
        }
   }

}

void toggleOnOff(OSCMessage &msg, int addrOffset){
	Serial.println(msg);
}
