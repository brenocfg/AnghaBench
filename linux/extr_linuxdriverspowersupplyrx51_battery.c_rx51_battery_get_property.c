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
union power_supply_propval {int intval; } ;
struct rx51_device_info {int dummy; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ INT_MIN ; 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 133 
#define  POWER_SUPPLY_PROP_PRESENT 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 struct rx51_device_info* power_supply_get_drvdata (struct power_supply*) ; 
 int rx51_battery_read_capacity (struct rx51_device_info*) ; 
 int rx51_battery_read_temperature (struct rx51_device_info*) ; 
 int rx51_battery_read_voltage (struct rx51_device_info*) ; 

__attribute__((used)) static int rx51_battery_get_property(struct power_supply *psy,
					enum power_supply_property psp,
					union power_supply_propval *val)
{
	struct rx51_device_info *di = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = 4200000;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = rx51_battery_read_voltage(di) ? 1 : 0;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = rx51_battery_read_voltage(di);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = rx51_battery_read_temperature(di);
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->intval = rx51_battery_read_capacity(di);
		break;
	default:
		return -EINVAL;
	}

	if (val->intval == INT_MAX || val->intval == INT_MIN)
		return -EINVAL;

	return 0;
}