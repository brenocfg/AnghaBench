#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct power_supply {TYPE_1__* desc; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_6__ {TYPE_2__* batteries; scalar_t__ individual_addressing; } ;
struct TYPE_5__ {unsigned long charge_stop; unsigned long charge_start; int /*<<< orphan*/  stop_support; int /*<<< orphan*/  start_support; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int BAT_PRIMARY ; 
 int EINVAL ; 
 int ENODEV ; 
#define  THRESHOLD_START 129 
#define  THRESHOLD_STOP 128 
 TYPE_3__ battery_info ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  pr_crit (char*,int) ; 
 struct power_supply* to_power_supply (struct device*) ; 
 int tpacpi_battery_get_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tpacpi_battery_set (int const,int,unsigned long) ; 

__attribute__((used)) static ssize_t tpacpi_battery_store(int what,
				    struct device *dev,
				    const char *buf, size_t count)
{
	struct power_supply *supply = to_power_supply(dev);
	unsigned long value;
	int battery, rval;
	/*
	 * Some systems have support for more than
	 * one battery. If that is the case,
	 * tpacpi_battery_probe marked that addressing
	 * them individually is supported, so we do that
	 * based on the device struct.
	 *
	 * On systems that are not supported, we assume
	 * the primary as most of the ACPI calls fail
	 * with "Any Battery" as the parameter.
	 */
	if (battery_info.individual_addressing)
		/* BAT_PRIMARY or BAT_SECONDARY */
		battery = tpacpi_battery_get_id(supply->desc->name);
	else
		battery = BAT_PRIMARY;

	rval = kstrtoul(buf, 10, &value);
	if (rval)
		return rval;

	switch (what) {
	case THRESHOLD_START:
		if (!battery_info.batteries[battery].start_support)
			return -ENODEV;
		/* valid values are [0, 99] */
		if (value < 0 || value > 99)
			return -EINVAL;
		if (value > battery_info.batteries[battery].charge_stop)
			return -EINVAL;
		if (tpacpi_battery_set(THRESHOLD_START, battery, value))
			return -ENODEV;
		battery_info.batteries[battery].charge_start = value;
		return count;

	case THRESHOLD_STOP:
		if (!battery_info.batteries[battery].stop_support)
			return -ENODEV;
		/* valid values are [1, 100] */
		if (value < 1 || value > 100)
			return -EINVAL;
		if (value < battery_info.batteries[battery].charge_start)
			return -EINVAL;
		battery_info.batteries[battery].charge_stop = value;
		/*
		 * When 100 is passed to stop, we need to flip
		 * it to 0 as that the EC understands that as
		 * "Default", which will charge to 100%
		 */
		if (value == 100)
			value = 0;
		if (tpacpi_battery_set(THRESHOLD_STOP, battery, value))
			return -EINVAL;
		return count;
	default:
		pr_crit("Wrong parameter: %d", what);
		return -EINVAL;
	}
	return count;
}