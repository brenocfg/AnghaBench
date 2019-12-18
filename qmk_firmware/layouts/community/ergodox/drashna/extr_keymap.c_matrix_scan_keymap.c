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
 int MOD_MASK_ALT ; 
 int MOD_MASK_CTRL ; 
 int MOD_MASK_SHIFT ; 
 int USB_LED_CAPS_LOCK ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_off () ; 
 int /*<<< orphan*/  ergodox_right_led_1_on () ; 
 int /*<<< orphan*/  ergodox_right_led_1_set (int) ; 
 int /*<<< orphan*/  ergodox_right_led_2_off () ; 
 int /*<<< orphan*/  ergodox_right_led_2_on () ; 
 int /*<<< orphan*/  ergodox_right_led_2_set (int) ; 
 int /*<<< orphan*/  ergodox_right_led_3_off () ; 
 int /*<<< orphan*/  ergodox_right_led_3_on () ; 
 int /*<<< orphan*/  ergodox_right_led_3_set (int) ; 
 int get_mods () ; 
 int get_oneshot_mods () ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  skip_leds ; 

void matrix_scan_keymap(void) {  // runs frequently to update info
    uint8_t modifiers     = get_mods();
    uint8_t led_usb_state = host_keyboard_leds();
    uint8_t one_shot      = get_oneshot_mods();

    if (!skip_leds) {
        ergodox_board_led_off();
        ergodox_right_led_1_off();
        ergodox_right_led_2_off();
        ergodox_right_led_3_off();

        // Since we're not using the LEDs here for layer indication anymore,
        // then lets use them for modifier indicators.  Shame we don't have 4...
        // Also, no "else", since we want to know each, independently.
        if ((modifiers | one_shot) & MOD_MASK_SHIFT || led_usb_state & (1 << USB_LED_CAPS_LOCK)) {
            ergodox_right_led_2_on();
            ergodox_right_led_2_set(50);
        }
        if ((modifiers | one_shot) & MOD_MASK_CTRL) {
            ergodox_right_led_1_on();
            ergodox_right_led_1_set(10);
        }
        if ((modifiers | one_shot) & MOD_MASK_ALT) {
            ergodox_right_led_3_on();
            ergodox_right_led_3_set(10);
        }
    }
}