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
 int DDRB ; 
 int DDRD ; 
 int PORTB ; 
 int PORTD ; 
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 

void led_set_user(uint8_t usb_led) {
  DDRB |= (1 << 4);
  DDRD |= (1 << 6) | (1 << 7);

  if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    PORTD |= (1 << 7);
  } else {
    PORTD &= ~(1 << 7);
  }

  if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    PORTB |= (1 << 4);
  } else {
    PORTB &= ~(1 << 4);
  }

  if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    PORTD |= (1 << 6);
  } else {
    PORTD &= ~(1 << 6);
  }
}