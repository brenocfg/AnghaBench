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
union power_supply_propval {int intval; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct pm860x_battery_info {int present; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  OCV_MODE_ACTIVE ; 
#define  POWER_SUPPLY_PROP_CAPACITY 134 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 133 
#define  POWER_SUPPLY_PROP_PRESENT 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 int calc_capacity (struct pm860x_battery_info*,int*) ; 
 int calc_ocv (struct pm860x_battery_info*,int*) ; 
 struct pm860x_battery_info* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int measure_current (struct pm860x_battery_info*,int*) ; 
 int measure_temp (struct pm860x_battery_info*,int*) ; 
 int measure_vbatt (struct pm860x_battery_info*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int pm860x_batt_get_prop(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
	struct pm860x_battery_info *info = dev_get_drvdata(psy->dev.parent);
	int data;
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = info->present;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = calc_capacity(info, &data);
		if (ret)
			return ret;
		if (data < 0)
			data = 0;
		else if (data > 100)
			data = 100;
		/* return 100 if battery is not attached */
		if (!info->present)
			data = 100;
		val->intval = data;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		/* return real vbatt Voltage */
		ret = measure_vbatt(info, OCV_MODE_ACTIVE, &data);
		if (ret)
			return ret;
		val->intval = data * 1000;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		/* return Open Circuit Voltage (not measured voltage) */
		ret = calc_ocv(info, &data);
		if (ret)
			return ret;
		val->intval = data * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = measure_current(info, &data);
		if (ret)
			return ret;
		val->intval = data;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		if (info->present) {
			ret = measure_temp(info, &data);
			if (ret)
				return ret;
			data *= 10;
		} else {
			/* Fake Temp 25C Without Battery */
			data = 250;
		}
		val->intval = data;
		break;
	default:
		return -ENODEV;
	}
	return 0;
}