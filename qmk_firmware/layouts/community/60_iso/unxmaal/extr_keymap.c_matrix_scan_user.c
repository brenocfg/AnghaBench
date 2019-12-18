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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  gh60_esc_led_off () ; 
 int /*<<< orphan*/  gh60_esc_led_on () ; 
 int /*<<< orphan*/  gh60_wasd_leds_off () ; 
 int /*<<< orphan*/  gh60_wasd_leds_on () ; 
 int layer_state ; 

void matrix_scan_user(void) {

// Layer LED indicators
// ESC led on when in function layer, WASD cluster leds enabled when on arrow cluster
  #ifdef KEYBOARD_gh60
    uint32_t layer = layer_state;
    if (layer & (1<<1)) {
        gh60_wasd_leds_on();
    } else {
        gh60_wasd_leds_off();
    }

    if (layer & (1<<2)) {
        gh60_esc_led_on();
    } else {
        gh60_esc_led_off();
    }
  #endif
}