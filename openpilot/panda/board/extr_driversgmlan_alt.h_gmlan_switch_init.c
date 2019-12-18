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
 int /*<<< orphan*/  GMLAN_LOW ; 
 int /*<<< orphan*/  GPIOB ; 
 int /*<<< orphan*/  GPIO_SWITCH ; 
 int /*<<< orphan*/  MODE_OUTPUT ; 
 int /*<<< orphan*/  gmlan_alt_mode ; 
 int gmlan_switch_below_timeout ; 
 int gmlan_switch_timeout_enable ; 
 int /*<<< orphan*/  inverted_bit_to_send ; 
 int /*<<< orphan*/  set_gpio_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setup_timer4 () ; 

void gmlan_switch_init(int timeout_enable) {
  gmlan_switch_timeout_enable = timeout_enable;
  gmlan_alt_mode = GPIO_SWITCH;
  gmlan_switch_below_timeout = 1;
  set_gpio_mode(GPIOB, 13, MODE_OUTPUT);

  setup_timer4();

  inverted_bit_to_send = GMLAN_LOW; //We got initialized, set the output low
}