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
 int DVRK ; 
 int NUMR ; 
 int USB_LED_CAPS_LOCK ; 
 int default_layer_state ; 
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
    if (layer_state & (1 << NUMR)) {
        ergodox_right_led_1_on();
    }
    // led 2: Dvorak layer
    if (default_layer_state == 1 << DVRK) {
        ergodox_right_led_2_on();
    }
    // led 3: caps lock
    if (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) {
      ergodox_right_led_3_on();
    }

}