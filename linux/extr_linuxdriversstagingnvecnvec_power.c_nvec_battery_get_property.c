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
union power_supply_propval {int /*<<< orphan*/  intval; int /*<<< orphan*/  strval; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct nvec_power {int /*<<< orphan*/  bat_type_enum; int /*<<< orphan*/  bat_model; int /*<<< orphan*/  bat_manu; int /*<<< orphan*/  bat_temperature; int /*<<< orphan*/  capacity_remain; int /*<<< orphan*/  critical_capacity; int /*<<< orphan*/  charge_last_full; int /*<<< orphan*/  charge_full_design; int /*<<< orphan*/  time_remain; int /*<<< orphan*/  bat_current_avg; int /*<<< orphan*/  bat_current_now; int /*<<< orphan*/  bat_voltage_now; int /*<<< orphan*/  bat_present; int /*<<< orphan*/  bat_cap; int /*<<< orphan*/  bat_status; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY 142 
#define  POWER_SUPPLY_PROP_CHARGE_EMPTY 141 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 140 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 139 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 138 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 137 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 136 
#define  POWER_SUPPLY_PROP_MANUFACTURER 135 
#define  POWER_SUPPLY_PROP_MODEL_NAME 134 
#define  POWER_SUPPLY_PROP_PRESENT 133 
#define  POWER_SUPPLY_PROP_STATUS 132 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 struct nvec_power* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nvec_battery_get_property(struct power_supply *psy,
				     enum power_supply_property psp,
				     union power_supply_propval *val)
{
	struct nvec_power *power = dev_get_drvdata(psy->dev.parent);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = power->bat_status;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = power->bat_cap;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = power->bat_present;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		val->intval = power->bat_voltage_now;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		val->intval = power->bat_current_now;
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		val->intval = power->bat_current_avg;
		break;
	case POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		val->intval = power->time_remain;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->intval = power->charge_full_design;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		val->intval = power->charge_last_full;
		break;
	case POWER_SUPPLY_PROP_CHARGE_EMPTY:
		val->intval = power->critical_capacity;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		val->intval = power->capacity_remain;
		break;
	case POWER_SUPPLY_PROP_TEMP:
		val->intval = power->bat_temperature;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = power->bat_manu;
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = power->bat_model;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = power->bat_type_enum;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}