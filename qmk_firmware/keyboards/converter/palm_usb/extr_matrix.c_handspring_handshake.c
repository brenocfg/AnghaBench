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

/* Variables and functions */
 int get_serial_byte () ; 

uint8_t handspring_handshake(void) {
    // should be sent 15 ms after power up. 
    // listen for up to 4 packets before giving up. 
    static uint8_t codeA=0;
 
    for (uint8_t i=0; i < 5; i++) {
        codeA=get_serial_byte();
        if ( 0xF9 == codeA) {
            if( 0xFB == get_serial_byte()) {
                return 1;
            }
        }
    }
    return 0;
}