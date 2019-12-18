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
 int /*<<< orphan*/  GPIOB ; 
#define  LED_GREEN 129 
#define  LED_RED 128 
 int /*<<< orphan*/  set_gpio_output (int /*<<< orphan*/ ,int,int) ; 

void pedal_set_led(uint8_t color, bool enabled) {
  switch (color){
    case LED_RED:
      set_gpio_output(GPIOB, 10, !enabled);
      break;
     case LED_GREEN:
      set_gpio_output(GPIOB, 11, !enabled);
      break;
    default:
      break;
  }
}