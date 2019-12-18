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
 int host_keyboard_leds () ; 
 int led_capslock ; 
 int led_numlock ; 
 int led_scrolllock ; 

void read_host_led_state(void) {
  uint8_t leds = host_keyboard_leds();
  if (leds & (1 << USB_LED_NUM_LOCK))    {
    if (led_numlock == false){
    led_numlock = true;}
    } else {
    if (led_numlock == true){
    led_numlock = false;}
    }
  if (leds & (1 << USB_LED_CAPS_LOCK))   {
    if (led_capslock == false){
    led_capslock = true;}
    } else {
    if (led_capslock == true){
    led_capslock = false;}
    }
  if (leds & (1 << USB_LED_SCROLL_LOCK)) {
    if (led_scrolllock == false){
    led_scrolllock = true;}
    } else {
    if (led_scrolllock == true){
    led_scrolllock = false;}
    }
}