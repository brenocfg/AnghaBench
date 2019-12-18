#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_3__ {scalar_t__ col; scalar_t__ row; } ;
typedef  TYPE_1__ keypos_t ;

/* Variables and functions */
 int KEY_LED_COUNT ; 
 int LED_BOOST_PEAK ; 
 int LED_BOOST_PROPAGATE ; 
 TYPE_1__* LED_TO_KEY_MAP ; 
 int get_led_boost_at_keypos (scalar_t__,scalar_t__) ; 
 int max (int,int) ; 

__attribute__((used)) static uint8_t get_propagated_boost_from_neighbors(int led_position) {
  if (led_position < 0 || led_position >= KEY_LED_COUNT) {
    return 0;
  }
  keypos_t led_keypos = LED_TO_KEY_MAP[led_position];
  uint8_t top_boost    = get_led_boost_at_keypos(led_keypos.row - 1, led_keypos.col);
  uint8_t bottom_boost = get_led_boost_at_keypos(led_keypos.row + 1, led_keypos.col);
  uint8_t left_boost   = get_led_boost_at_keypos(led_keypos.row, led_keypos.col - 1);
  uint8_t right_boost  = get_led_boost_at_keypos(led_keypos.row, led_keypos.col + 1);
  uint8_t max_boost = max(max(top_boost, bottom_boost), max(left_boost, right_boost));
  if (max_boost > LED_BOOST_PEAK) {
    max_boost = LED_BOOST_PEAK;
  }
  return max_boost * LED_BOOST_PROPAGATE;
}