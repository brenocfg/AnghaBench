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

/* Variables and functions */
 int USB_LED_CAPS_LOCK ; 
 int USB_LED_NUM_LOCK ; 
 int USB_LED_SCROLL_LOCK ; 
 int host_keyboard_leds () ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

const char *read_host_led_state(void) {
  static char led_str[24];
  strcpy(led_str, (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NMLK" : "    ");
  strcat(led_str, (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? " CAPS" : "    ");
  strcat(led_str, (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? " SCLK" : "     ");
  return led_str;
}