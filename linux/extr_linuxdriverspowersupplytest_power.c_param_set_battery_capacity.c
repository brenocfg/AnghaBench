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
struct kernel_param {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t TEST_BATTERY ; 
 int battery_capacity ; 
 int /*<<< orphan*/  signal_power_supply_changed (int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/ * test_power_supplies ; 

__attribute__((used)) static int param_set_battery_capacity(const char *key,
					const struct kernel_param *kp)
{
	int tmp;

	if (1 != sscanf(key, "%d", &tmp))
		return -EINVAL;

	battery_capacity = tmp;
	signal_power_supply_changed(test_power_supplies[TEST_BATTERY]);
	return 0;
}