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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  debug (char*) ; 
 int /*<<< orphan*/  debug_hex (scalar_t__) ; 
 scalar_t__ serial_recv () ; 

uint8_t get_serial_byte(void) {
    static uint8_t code;
    while(1) {
        code = serial_recv();
        if (code) { 
            debug_hex(code); debug(" ");
            return code;
        }
    }
}