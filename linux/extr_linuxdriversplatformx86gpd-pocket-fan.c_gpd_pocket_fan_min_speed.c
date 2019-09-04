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
 scalar_t__ power_supply_is_system_supplied () ; 
 int speed_on_ac ; 

__attribute__((used)) static int gpd_pocket_fan_min_speed(void)
{
	if (power_supply_is_system_supplied())
		return speed_on_ac;
	else
		return 0;
}