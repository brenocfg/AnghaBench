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
 int biton32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ergodox_board_led_off () ; 
 int /*<<< orphan*/  ergodox_right_led_off (int) ; 
 int /*<<< orphan*/  ergodox_right_led_on (int) ; 
 int /*<<< orphan*/  ergodox_right_led_set (int,int) ; 
 int /*<<< orphan*/  layer_state ; 

void matrix_scan_user(void) {
    /* leds is a static array holding the current brightness of each of the
     * three keyboard LEDs. It's 4 long simply to avoid the ugliness of +1s and
     * -1s in the code below, and because wasting a byte really doesn't matter
     * that much (no, it *doesn't*, stop whinging!). Note that because it's
     * static it'll maintain state across invocations of this routine.
     */
    static uint8_t leds[4];
    uint8_t led;
    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();

    /* Loop over each LED/layer */
    for (led = 1; led <= 3; ++led) {
        /* If the current layer matches the current LED, increment its
         * brightness by 1 up to a maximum of 255. If the current layer doesn't
         * match, decrement its brightness by 1 down to a minimum of zero.
         */
        leds[led] += (layer == led) ?
            (leds[led] < 255 ? 1 : 0):
            (leds[led] > 0 ? -1 : 0);
        /* Set LED state according to the new brightness */
        if (leds[led]) {
            ergodox_right_led_on(led);
            ergodox_right_led_set(led, leds[led]);
        }
        else {
            ergodox_right_led_off(led);
        }
    }


}