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
 int STATE_LED_CAPS_LOCK ; 
 int STATE_LED_NUM_LOCK ; 
 int STATE_LED_SCROLL_LOCK ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int backlight_state_led ; 
 int /*<<< orphan*/  backlight_update_state () ; 

void led_set_kb(uint8_t usb_led)
{
  if(usb_led & (1<<USB_LED_CAPS_LOCK)) {
    backlight_state_led |=   1<<STATE_LED_CAPS_LOCK;
  } else {
    backlight_state_led &= ~(1<<STATE_LED_CAPS_LOCK);
  }
  if(usb_led & (1<<USB_LED_SCROLL_LOCK)) {
    backlight_state_led |=   1<<STATE_LED_SCROLL_LOCK;
  } else {
    backlight_state_led &= ~(1<<STATE_LED_SCROLL_LOCK);
  }
  if(usb_led & (1<<USB_LED_NUM_LOCK)) {
    backlight_state_led |=   1<<STATE_LED_NUM_LOCK;
  } else {
    backlight_state_led &= ~(1<<STATE_LED_NUM_LOCK);
  }
  backlight_update_state();
}