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
 int /*<<< orphan*/ * led_boosts ; 

__attribute__((used)) static void set_new_led_boosts(uint8_t* new_led_boosts) {
  for (int i = 0; i < ISSI3733_LED_COUNT; i++) {
    led_boosts[i] = new_led_boosts[i];
  }
}