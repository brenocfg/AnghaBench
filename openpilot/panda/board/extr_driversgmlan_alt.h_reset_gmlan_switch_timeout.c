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
 int /*<<< orphan*/  GMLAN_TICKS_PER_SECOND ; 
 int /*<<< orphan*/  GPIO_SWITCH ; 
 int /*<<< orphan*/  can_timeout_counter ; 
 int /*<<< orphan*/  gmlan_alt_mode ; 
 int gmlan_switch_below_timeout ; 

void reset_gmlan_switch_timeout(void) {
  can_timeout_counter = GMLAN_TICKS_PER_SECOND;
  gmlan_switch_below_timeout = 1;
  gmlan_alt_mode = GPIO_SWITCH;
}