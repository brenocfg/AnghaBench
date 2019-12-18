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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  hex_to_keycode (int) ; 
 int /*<<< orphan*/  tap_code (int /*<<< orphan*/ ) ; 

void register_hex(uint16_t hex) {
    for (int i = 3; i >= 0; i--) {
        uint8_t digit = ((hex >> (i * 4)) & 0xF);
        tap_code(hex_to_keycode(digit));
    }
}