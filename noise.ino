

#include "RF24.h"
#include "printf.h"

//
// Hardware configuration
//

#define CE_PIN 7
#define CSN_PIN 8
// instantiate an object for the nRF24L01 transceiver
RF24 radio(CE_PIN, CSN_PIN);
uint64_t address[2] = { 0x3030303030LL, 0x3030303030LL};

void printHeader();  // prototype function for printing the channels' header

byte payload[32];

void setup(void) {

  Serial.begin(115200);

  // Setup and configure rf radio
  if (!radio.begin()) {
    Serial.println(F("radio hardware not responding!"));
    while (true) {
      // hold in an infinite loop
    }
  }

  radio.setAutoAck(false);   // Don't acknowledge arbitrary signals
  radio.disableCRC();        // Accept any signal we find
  radio.setDataRate(RF24_1MBPS);
  
  
  radio.setPayloadSize(sizeof(payload));

  radio.openWritingPipe(address[0]);  // always uses pipe 0
  radio.openReadingPipe(1, address[1]);  // using pipe 1

  radio.setChannel(0);

  radio.startListening();
  radio.stopListening();
  radio.flush_rx();


}

void loop(void) {
  for (int i=0;i<100;i++){
    radio.setChannel(i);
    radio.write(&payload[0], sizeof(payload));
    Serial.println(i);
  }
  
 
}
