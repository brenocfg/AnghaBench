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
 int /*<<< orphan*/  CAPSLOCK_PORT ; 
 int /*<<< orphan*/  DDRD ; 
 int /*<<< orphan*/  PORTD ; 
 int USB_LED_CAPS_LOCK ; 

__attribute__ ((weak))
void led_set_user(uint8_t usb_led) {
    /*
    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
      // turn on
      DDRD  |= NUMLOCK_PORT;
      PORTD |= NUMLOCK_PORT;
    } else {
      // turn off
      DDRD  &= ~NUMLOCK_PORT;
      PORTD &= ~NUMLOCK_PORT;
    }
     */
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
      DDRD  |= CAPSLOCK_PORT;
      PORTD |= CAPSLOCK_PORT;
    } else {
      DDRD  &= ~CAPSLOCK_PORT;
      PORTD &= ~CAPSLOCK_PORT;
    }
    /*
    if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
      DDRD  |= SCROLLLOCK_PORT;
      PORTD |= SCROLLLOCK_PORT;
    } else {
      DDRD  &= ~SCROLLLOCK_PORT;
      PORTD &= ~SCROLLLOCK_PORT;
    }
     */
}