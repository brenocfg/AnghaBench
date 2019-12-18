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
 int /*<<< orphan*/  sixshooter_led_0_off () ; 
 int /*<<< orphan*/  sixshooter_led_1_off () ; 
 int /*<<< orphan*/  sixshooter_led_2_off () ; 
 int /*<<< orphan*/  sixshooter_led_3_off () ; 
 int /*<<< orphan*/  sixshooter_led_4_off () ; 
 int /*<<< orphan*/  sixshooter_led_5_off () ; 

inline void sixshooter_led_all_off(void) {
  sixshooter_led_0_off();
  sixshooter_led_1_off();
  sixshooter_led_2_off();
  sixshooter_led_3_off();
  sixshooter_led_4_off();
  sixshooter_led_5_off();
}