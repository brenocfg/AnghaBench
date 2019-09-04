#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct power_supply_info {int voltage_max_design; long voltage_min_design; } ;
struct power_supply {int dummy; } ;
struct jz_battery {TYPE_1__* pdata; } ;
struct TYPE_2__ {struct power_supply_info info; } ;

/* Variables and functions */
 long jz_battery_read_voltage (struct jz_battery*) ; 
 struct jz_battery* psy_to_jz_battery (struct power_supply*) ; 

__attribute__((used)) static int jz_battery_get_capacity(struct power_supply *psy)
{
	struct jz_battery *jz_battery = psy_to_jz_battery(psy);
	struct power_supply_info *info = &jz_battery->pdata->info;
	long voltage;
	int ret;
	int voltage_span;

	voltage = jz_battery_read_voltage(jz_battery);

	if (voltage < 0)
		return voltage;

	voltage_span = info->voltage_max_design - info->voltage_min_design;
	ret = ((voltage - info->voltage_min_design) * 100) / voltage_span;

	if (ret > 100)
		ret = 100;
	else if (ret < 0)
		ret = 0;

	return ret;
}