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
 int CONFIG_THERMAL_EMERGENCY_POWEROFF_DELAY_MS ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thermal_emergency_poweroff_work ; 

__attribute__((used)) static void thermal_emergency_poweroff(void)
{
	int poweroff_delay_ms = CONFIG_THERMAL_EMERGENCY_POWEROFF_DELAY_MS;
	/*
	 * poweroff_delay_ms must be a carefully profiled positive value.
	 * Its a must for thermal_emergency_poweroff_work to be scheduled
	 */
	if (poweroff_delay_ms <= 0)
		return;
	schedule_delayed_work(&thermal_emergency_poweroff_work,
			      msecs_to_jiffies(poweroff_delay_ms));
}