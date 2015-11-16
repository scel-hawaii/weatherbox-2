/*******************************************
 *
 *    File: transmit.cpp
 *    REIS Weatherbox Firmware
 *
 *    File containing Transmission functions
 *
 ******************************************/


/* Necessary Libraries */
#include "transmit.h"


/******************************************
 *
 *   Name:        Packet_Clear
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Clears/Initializes the packet to
 *                    NULL.
 *
 *****************************************/
void Packet_Clear(uint8_t *packet){

    /* Variables Declarations */
    int i = 0;

    /* Set packet to NULL */
    for(i = 0; i < MAX_SIZE; i++){
        packet[i] = '\0';
    }
}

/******************************************
 *
 *   Name:        Packet_TransmitUART
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Transmits using Arduino Xbee functions,
 *                    Xbees must be in API mode.
 *
 *****************************************/
void Packet_TransmitUART(uint8_t *packet){

    /* Variable Declarations */
    XBee xbee = XBee();    //Create Xbee Object
    int length = 0;        //Length of the packet to be sent
    int i = 0;             //Variable to be used to iterate across the packet

    /* Obtain address of receiving end */
    XBeeAddress64 addr64 = XBeeAddress64(0,0); //!!TEST if this gets right addr

    /* Get length of packet */
    length = strlen((char *) packet);

#ifdef DEBUG_S
    /* Debug */
    Serial.print("\nLength is: ");
    Serial.print(length);
#endif

    /* Transfer the packet */
    ZBTxRequest zbTx = ZBTxRequest(addr64, packet, length);
    xbee.send(zbTx);
}

/******************************************
 *
 *   Name:        Packet_TransmitBIN
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Transmits using Arduino Xbee functions,
 *                    the packet is transfered as a
 *                    binary packet.
 *
 *****************************************/
void Packet_TransmitBIN(uint8_t *packet){

    /* Packet to be transmitted */
    uint8_t payload[MAX_SIZE];

    /* Clear the payload */
    memset(payload, '\0', sizeof(payload));

    /* Obtain length of the packet */
    length = strlen((char *) packet);

#ifdef DEBUG_S
    /* Debug */
    Serial.print("\nLength is: ");
    Serial.print(length);
#endif

    /* Transfer information into payload */
    memcpy(payload, &packet, length);
    
    /* Transfer the payload */
    ZBTxRequest zbTx = ZBTxRequest(addr64, payload, length);
    xbee.send(zbTx);
}

/******************************************
 *
 *   Name:        Test_Packet_Gen
 *   Returns:     Nothing
 *   Parameter:   uint8_t *packet
 *   Description: Constructs a packet with hard-coded
 *                    information.  Used for the initial
 *                    test of the Transmission functions.
 *                    To be replaced by Packet Construction.
 *
 *****************************************/
void Test_Packet_Gen(uint8_t *packet){

    /* Necessary Variables */
    int i = 0;

    /* Set up array */
    String s;
    
    /* Fill with Hard-coded information */
    s = "test yes";
    s += '\0';

    /* Put array information into Packet */
    for(i = 0; i < s.length(); i++){
      packet[i] = s[i];
    }
}
