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

/* Variables and functions */
 size_t ISSI3733_LED_COUNT ; 
 int /*<<< orphan*/  LED_BOOST_PEAK ; 
 int /*<<< orphan*/ * led_boosts ; 
 size_t map_key_position_to_led_index (size_t,size_t) ; 

__attribute__((used)) static void set_nearest_led_to_max(uint8_t col, uint8_t row) {
  uint8_t led_index = map_key_position_to_led_index(col, row);
  if (led_index >= 0 && led_index < ISSI3733_LED_COUNT) {
    led_boosts[led_index] = LED_BOOST_PEAK;
  }
}