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
 int /*<<< orphan*/  REG_ENFORCE_GRACE_MS ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_check_chans ; 
 int /*<<< orphan*/  system_power_efficient_wq ; 

__attribute__((used)) static void reg_check_channels(void)
{
	/*
	 * Give usermode a chance to do something nicer (move to another
	 * channel, orderly disconnection), before forcing a disconnection.
	 */
	mod_delayed_work(system_power_efficient_wq,
			 &reg_check_chans,
			 msecs_to_jiffies(REG_ENFORCE_GRACE_MS));
}