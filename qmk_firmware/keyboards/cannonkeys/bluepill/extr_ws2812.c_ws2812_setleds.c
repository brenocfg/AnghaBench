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
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  set_led_color_rgb (int /*<<< orphan*/ ,size_t) ; 

void ws2812_setleds(LED_TYPE *ledarray, uint16_t number_of_leds) {
  uint8_t i = 0;
  while (i < number_of_leds) {
    set_led_color_rgb(ledarray[i], i);
    i++;
  }
}