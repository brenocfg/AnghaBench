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
 int ISSI3733_LED_COUNT ; 
 int /*<<< orphan*/  last_boost_update ; 
 scalar_t__ led_boost_index ; 
 scalar_t__* led_boosts ; 
 scalar_t__ led_cur_index ; 
 int /*<<< orphan*/  timer_read () ; 

void rgb_matrix_init_user(void) {
  for (int i = 0; i < ISSI3733_LED_COUNT; i++) {
    led_boosts[i] = 0;
  }
  last_boost_update = timer_read();
  led_boost_index = 0;
  led_cur_index = 0;
}