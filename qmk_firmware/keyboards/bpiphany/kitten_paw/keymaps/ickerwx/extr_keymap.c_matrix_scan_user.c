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
 scalar_t__ MOUSE1 ; 
 scalar_t__ MOUSE2 ; 
 scalar_t__ PROG1 ; 
 scalar_t__ PROG2 ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 scalar_t__ biton32 (int /*<<< orphan*/ ) ; 
 scalar_t__ current_layer_global ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  layer_state ; 
 int /*<<< orphan*/  led_set_kb (int) ; 

void matrix_scan_user(void) {
    uint8_t layer;
    layer = biton32(layer_state);

    if (current_layer_global != layer) {
        current_layer_global = layer;

        // unset CAPSLOCK and SCROLL LOCK LEDs
        led_set_kb(host_keyboard_leds() & ~(1<<USB_LED_CAPS_LOCK));
        led_set_kb(host_keyboard_leds() & ~(1<<USB_LED_SCROLL_LOCK));
        // set SCROLL LOCK LED when the mouse layer is active, CAPS LOCK when PROG layer is active
        if (layer == MOUSE1 || layer == MOUSE2) {
          led_set_kb(host_keyboard_leds() | (1<<USB_LED_SCROLL_LOCK));
        } else if (layer == PROG1 || layer == PROG2) {
          led_set_kb(host_keyboard_leds() | (1<<USB_LED_CAPS_LOCK));
        }
    }
}