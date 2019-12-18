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

/* Variables and functions */
 int /*<<< orphan*/  LAYER_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUMP ; 
 int /*<<< orphan*/  SYMB ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int td_led_override ; 

void matrix_scan_user(void) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (td_led_override) {
    case 1:
        ergodox_right_led_1_on();
        break;
    case 2:
        ergodox_right_led_2_on();
        break;
    default:
        // Layer 1 and 2 are both overlay layers, so they could both be on. This
        // means we can't use the lazy check of checking for the first significant
        // bit.
        if (LAYER_ON(SYMB)) {
            ergodox_right_led_1_on();
        }
        if (LAYER_ON(NUMP)) {
            ergodox_right_led_2_on();
        }
    }
}