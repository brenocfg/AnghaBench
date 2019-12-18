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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  hex_to_keycode (scalar_t__) ; 
 int /*<<< orphan*/  register_code (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_code (int /*<<< orphan*/ ) ; 

void register_hex32(uint32_t hex) {
    bool onzerostart = true;
    for (int i = 7; i >= 0; i--) {
        if (i <= 3) {
            onzerostart = false;
        }
        uint8_t digit = ((hex >> (i * 4)) & 0xF);
        if (digit == 0) {
            if (!onzerostart) {
                register_code(hex_to_keycode(digit));
                unregister_code(hex_to_keycode(digit));
            }
        } else {
            register_code(hex_to_keycode(digit));
            unregister_code(hex_to_keycode(digit));
            onzerostart = false;
        }
    }
}