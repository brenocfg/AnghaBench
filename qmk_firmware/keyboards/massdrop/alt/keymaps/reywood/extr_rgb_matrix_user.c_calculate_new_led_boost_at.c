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
typedef  scalar_t__ uint8_t ;

/* Variables and functions */
 scalar_t__ LED_BOOST_DECAY ; 
 scalar_t__ LED_BOOST_PEAK ; 
 scalar_t__ get_propagated_boost_from_neighbors (int) ; 
 scalar_t__* led_boosts ; 

__attribute__((used)) static uint8_t calculate_new_led_boost_at(int index) {
  uint8_t decayed_boost = led_boosts[index] * LED_BOOST_DECAY;
  uint8_t propagated_boost = get_propagated_boost_from_neighbors(index);
  uint8_t new_boost = (propagated_boost > decayed_boost) ? propagated_boost : decayed_boost;
  if (new_boost > LED_BOOST_PEAK) {
    new_boost = LED_BOOST_PEAK;
  }
  return new_boost;
}