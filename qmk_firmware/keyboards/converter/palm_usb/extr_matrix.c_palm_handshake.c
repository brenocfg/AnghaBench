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

uint8_t palm_handshake(void) {
    // assumes something has seen DCD go high, we've toggled RTS 
    // and we now need to verify handshake. 
    // listen for up to 4 packets before giving up. 
    // usually I get the sequence FF FA FD
    static uint8_t codeA=0;
 
    for (uint8_t i=0; i < 5; i++) {
        codeA=get_serial_byte();
        if ( 0xFA == codeA) {
            if( 0xFD == get_serial_byte()) {
                return 1;
            }
        }
    }
    return 0;
}