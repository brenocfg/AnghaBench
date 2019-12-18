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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  indicator_leds_set (int*) ; 
 int layer_state ; 

void led_set_kb(uint8_t usb_led) {
    bool status[8] = {
    host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK), /* LED 3 */
    host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK),   /* LED 2 */
    host_keyboard_leds() & (1<<USB_LED_NUM_LOCK),    /* LED 1 */

    layer_state & (1<<2),                            /* LED 6 */
    layer_state & (1<<1),                            /* LED 5 */
    layer_state & (1<<0) ? 0: 1,                     /* LED 4 */

    layer_state & (1<<5),                            /* LED 8 */
    layer_state & (1<<4)                             /* LED 7 */
  };

  indicator_leds_set(status);
}