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
typedef  int /*<<< orphan*/  LED_TYPE ;

/* Variables and functions */
 int NB_LEDS ; 
 int /*<<< orphan*/  set_led_color_rgb (int /*<<< orphan*/ ,int) ; 

void set_leds_color_rgb(LED_TYPE color){
  for(int i = 0; i < NB_LEDS; i++)
    set_led_color_rgb(color, i);
}