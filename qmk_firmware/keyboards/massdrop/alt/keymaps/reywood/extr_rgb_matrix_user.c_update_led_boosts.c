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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int ISSI3733_LED_COUNT ; 
 scalar_t__ LED_BOOST_REFRESH_INTERVAL_IN_MS ; 
 int /*<<< orphan*/  calculate_new_led_boosts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  last_boost_update ; 
 int /*<<< orphan*/  set_new_led_boosts (int /*<<< orphan*/ *) ; 
 scalar_t__ timer_elapsed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_read () ; 

__attribute__((used)) static void update_led_boosts(void) {
  if (timer_elapsed(last_boost_update) > LED_BOOST_REFRESH_INTERVAL_IN_MS) {
    last_boost_update = timer_read();

    uint8_t new_led_boosts[ISSI3733_LED_COUNT];
    calculate_new_led_boosts(new_led_boosts);
    set_new_led_boosts(new_led_boosts);
  }
}