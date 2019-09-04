#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int intval; int /*<<< orphan*/  strval; } ;
struct power_supply {int dummy; } ;
struct TYPE_3__ {scalar_t__ flags; int /*<<< orphan*/  health; int /*<<< orphan*/  power_avg; int /*<<< orphan*/  energy; int /*<<< orphan*/  cycle_count; int /*<<< orphan*/  charge_full; int /*<<< orphan*/  time_to_full; int /*<<< orphan*/  time_to_empty_avg; int /*<<< orphan*/  time_to_empty; int /*<<< orphan*/  temperature; int /*<<< orphan*/  capacity; } ;
struct TYPE_4__ {int /*<<< orphan*/  work; } ;
struct bq27xxx_device_info {TYPE_1__ cache; int /*<<< orphan*/  charge_design_full; int /*<<< orphan*/  lock; TYPE_2__ work; scalar_t__ last_update; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  BQ27XXX_MANUFACTURER ; 
 int EINVAL ; 
 int ENODEV ; 
 int HZ ; 
#define  POWER_SUPPLY_PROP_CAPACITY 148 
#define  POWER_SUPPLY_PROP_CAPACITY_LEVEL 147 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 146 
#define  POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN 145 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 144 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 143 
#define  POWER_SUPPLY_PROP_CYCLE_COUNT 142 
#define  POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN 141 
#define  POWER_SUPPLY_PROP_ENERGY_NOW 140 
#define  POWER_SUPPLY_PROP_HEALTH 139 
#define  POWER_SUPPLY_PROP_MANUFACTURER 138 
#define  POWER_SUPPLY_PROP_POWER_AVG 137 
#define  POWER_SUPPLY_PROP_PRESENT 136 
#define  POWER_SUPPLY_PROP_STATUS 135 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 134 
#define  POWER_SUPPLY_PROP_TEMP 133 
#define  POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG 132 
#define  POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW 131 
#define  POWER_SUPPLY_PROP_TIME_TO_FULL_NOW 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 int bq27xxx_battery_capacity_level (struct bq27xxx_device_info*,union power_supply_propval*) ; 
 int bq27xxx_battery_current (struct bq27xxx_device_info*,union power_supply_propval*) ; 
 int /*<<< orphan*/  bq27xxx_battery_poll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bq27xxx_battery_read_nac (struct bq27xxx_device_info*) ; 
 int bq27xxx_battery_status (struct bq27xxx_device_info*,union power_supply_propval*) ; 
 int bq27xxx_battery_voltage (struct bq27xxx_device_info*,union power_supply_propval*) ; 
 int bq27xxx_simple_value (int /*<<< orphan*/ ,union power_supply_propval*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct bq27xxx_device_info* power_supply_get_drvdata (struct power_supply*) ; 
 scalar_t__ time_is_before_jiffies (scalar_t__) ; 

__attribute__((used)) static int bq27xxx_battery_get_property(struct power_supply *psy,
					enum power_supply_property psp,
					union power_supply_propval *val)
{
	int ret = 0;
	struct bq27xxx_device_info *di = power_supply_get_drvdata(psy);

	mutex_lock(&di->lock);
	if (time_is_before_jiffies(di->last_update + 5 * HZ)) {
		cancel_delayed_work_sync(&di->work);
		bq27xxx_battery_poll(&di->work.work);
	}
	mutex_unlock(&di->lock);

	if (psp != POWER_SUPPLY_PROP_PRESENT && di->cache.flags < 0)
		return -ENODEV;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = bq27xxx_battery_status(di, val);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = bq27xxx_battery_voltage(di, val);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = di->cache.flags < 0 ? 0 : 1;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = bq27xxx_battery_current(di, val);
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		ret = bq27xxx_simple_value(di->cache.capacity, val);
		break;
	case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		ret = bq27xxx_battery_capacity_level(di, val);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		ret = bq27xxx_simple_value(di->cache.temperature, val);
		if (ret == 0)
			val->intval -= 2731; /* convert decidegree k to c */
		break;
	case POWER_SUPPLY_PROP_TIME_TO_EMPTY_NOW:
		ret = bq27xxx_simple_value(di->cache.time_to_empty, val);
		break;
	case POWER_SUPPLY_PROP_TIME_TO_EMPTY_AVG:
		ret = bq27xxx_simple_value(di->cache.time_to_empty_avg, val);
		break;
	case POWER_SUPPLY_PROP_TIME_TO_FULL_NOW:
		ret = bq27xxx_simple_value(di->cache.time_to_full, val);
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		ret = bq27xxx_simple_value(bq27xxx_battery_read_nac(di), val);
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		ret = bq27xxx_simple_value(di->cache.charge_full, val);
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		ret = bq27xxx_simple_value(di->charge_design_full, val);
		break;
	/*
	 * TODO: Implement these to make registers set from
	 * power_supply_battery_info visible in sysfs.
	 */
	case POWER_SUPPLY_PROP_ENERGY_FULL_DESIGN:
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		return -EINVAL;
	case POWER_SUPPLY_PROP_CYCLE_COUNT:
		ret = bq27xxx_simple_value(di->cache.cycle_count, val);
		break;
	case POWER_SUPPLY_PROP_ENERGY_NOW:
		ret = bq27xxx_simple_value(di->cache.energy, val);
		break;
	case POWER_SUPPLY_PROP_POWER_AVG:
		ret = bq27xxx_simple_value(di->cache.power_avg, val);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		ret = bq27xxx_simple_value(di->cache.health, val);
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = BQ27XXX_MANUFACTURER;
		break;
	default:
		return -EINVAL;
	}

	return ret;
}