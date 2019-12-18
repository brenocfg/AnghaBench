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
 scalar_t__ IS_CA_MULT_ENABLED () ; 
 int LR_NUMR ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int host_keyboard_leds () ; 
 int layer_state ; 

void matrix_scan_user(void) {

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    // led 1: numeric layer
    if (layer_state & (1 << LR_NUMR)) {
        ergodox_right_led_1_on();
    }
    // led 2: BÉPO over Canadian Multilingual
    if (IS_CA_MULT_ENABLED()) {
        ergodox_right_led_2_on();
    }
    // led 3: caps lock
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
      ergodox_right_led_3_on();
    }
}