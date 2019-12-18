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
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int /*<<< orphan*/  indicator_leds_set (int*) ; 
 int layer_state ; 
 int /*<<< orphan*/  led_set_user (int) ; 

void led_set_kb(uint8_t usb_led) {
  bool leds[8] = {
    usb_led & (1<<USB_LED_CAPS_LOCK),
    usb_led & (1<<USB_LED_SCROLL_LOCK),
    usb_led & (1<<USB_LED_NUM_LOCK),
    layer_state & (1<<1),
    layer_state & (1<<2),
    layer_state & (1<<3),
    layer_state & (1<<4),
    layer_state & (1<<5)
  };
  indicator_leds_set(leds);

  led_set_user(usb_led);
}