#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint64_t ;
typedef  int uint16_t ;

/* Variables and functions */

void buildFrame(uint8_t *frame, uint64_t remote, uint8_t button, uint16_t code) {
    // NODE_DBG("remote: %x\n", remote);
    // NODE_DBG("button: %x\n", button);
    // NODE_DBG("rolling code: %x\n", code);
    frame[0] = 0xA7; // Encryption key. Doesn't matter much
    frame[1] = button << 4; // Which button did you press? The 4 LSB will be the checksum
    frame[2] = code >> 8; // Rolling code (big endian)
    frame[3] = code;         // Rolling code
    frame[4] = remote >> 16; // Remote address
    frame[5] = remote >> 8; // Remote address
    frame[6] = remote;         // Remote address
    // frame[7] = 0x80;
    // frame[8] = 0x0;
    // frame[9] = 0x0;

    // NODE_DBG("Frame:\t\t\t%02x %02x %02x %02x %02x %02x %02x\n", frame[0], frame[1], frame[2], frame[3], frame[4], frame[5], frame[6]);
    // Checksum calculation: a XOR of all the nibbles
    uint8_t checksum = 0;
    for(uint8_t i = 0; i < 7; i++) {
        checksum = checksum ^ frame[i] ^ (frame[i] >> 4);
    }
    checksum &= 0b1111; // We keep the last 4 bits only

    //Checksum integration
    frame[1] |= checksum; //    If a XOR of all the nibbles is equal to 0, the blinds will consider the checksum ok.
    // NODE_DBG("With checksum:\t%02x %02x %02x %02x %02x %02x %02x\n", frame[0], frame[1], frame[2], frame[3], frame[4], frame[5], frame[6]);

    // Obfuscation: a XOR of all the uint8_ts
    for(uint8_t i = 1; i < 7; i++) {
        frame[i] ^= frame[i-1];
    }
    // NODE_DBG("Obfuscated:\t\t%02x %02x %02x %02x %02x %02x %02x\n", frame[0], frame[1], frame[2], frame[3], frame[4], frame[5], frame[6]);
}