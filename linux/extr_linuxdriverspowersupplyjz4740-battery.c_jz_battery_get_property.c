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
struct power_supply_info {int technology; long voltage_min_design; int voltage_max_design; } ;
struct power_supply {int dummy; } ;
struct jz_battery {int status; TYPE_1__* pdata; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {struct power_supply_info info; } ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
#define  POWER_SUPPLY_PROP_CAPACITY 135 
#define  POWER_SUPPLY_PROP_HEALTH 134 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int jz_battery_get_capacity (struct power_supply*) ; 
 void* jz_battery_read_voltage (struct jz_battery*) ; 
 struct jz_battery* psy_to_jz_battery (struct power_supply*) ; 

__attribute__((used)) static int jz_battery_get_property(struct power_supply *psy,
	enum power_supply_property psp, union power_supply_propval *val)
{
	struct jz_battery *jz_battery = psy_to_jz_battery(psy);
	struct power_supply_info *info = &jz_battery->pdata->info;
	long voltage;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = jz_battery->status;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = jz_battery->pdata->info.technology;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		voltage = jz_battery_read_voltage(jz_battery);
		if (voltage < info->voltage_min_design)
			val->intval = POWER_SUPPLY_HEALTH_DEAD;
		else
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = jz_battery_get_capacity(psy);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = jz_battery_read_voltage(jz_battery);
		if (val->intval < 0)
			return val->intval;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX_DESIGN:
		val->intval = info->voltage_max_design;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->intval = info->voltage_min_design;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = 1;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}