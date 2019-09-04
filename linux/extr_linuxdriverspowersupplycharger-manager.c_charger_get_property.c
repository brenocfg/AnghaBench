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
struct power_supply {int dummy; } ;
struct charger_manager {struct charger_desc* desc; int /*<<< orphan*/  emergency_stop; } ;
struct charger_desc {int fullbatt_uV; int /*<<< orphan*/  psy_fuel_gauge; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int POWER_SUPPLY_HEALTH_COLD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
#define  POWER_SUPPLY_PROP_CAPACITY 138 
#define  POWER_SUPPLY_PROP_CHARGE_FULL 137 
#define  POWER_SUPPLY_PROP_CHARGE_NOW 136 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 135 
#define  POWER_SUPPLY_PROP_HEALTH 134 
#define  POWER_SUPPLY_PROP_ONLINE 133 
#define  POWER_SUPPLY_PROP_PRESENT 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_TEMP 130 
#define  POWER_SUPPLY_PROP_TEMP_AMBIENT 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 int POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_NOT_CHARGING ; 
 int cm_get_battery_temperature (struct charger_manager*,int*) ; 
 int get_batt_uV (struct charger_manager*,int*) ; 
 int /*<<< orphan*/  is_batt_present (struct charger_manager*) ; 
 int /*<<< orphan*/  is_charging (struct charger_manager*) ; 
 int /*<<< orphan*/  is_ext_pwr_online (struct charger_manager*) ; 
 int /*<<< orphan*/  is_full_charged (struct charger_manager*) ; 
 struct power_supply* power_supply_get_by_name (int /*<<< orphan*/ ) ; 
 struct charger_manager* power_supply_get_drvdata (struct power_supply*) ; 
 int power_supply_get_property (struct power_supply*,int const,union power_supply_propval*) ; 
 int /*<<< orphan*/  power_supply_put (struct power_supply*) ; 

__attribute__((used)) static int charger_get_property(struct power_supply *psy,
		enum power_supply_property psp,
		union power_supply_propval *val)
{
	struct charger_manager *cm = power_supply_get_drvdata(psy);
	struct charger_desc *desc = cm->desc;
	struct power_supply *fuel_gauge = NULL;
	int ret = 0;
	int uV;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (is_charging(cm))
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else if (is_ext_pwr_online(cm))
			val->intval = POWER_SUPPLY_STATUS_NOT_CHARGING;
		else
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		if (cm->emergency_stop > 0)
			val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		else if (cm->emergency_stop < 0)
			val->intval = POWER_SUPPLY_HEALTH_COLD;
		else
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		if (is_batt_present(cm))
			val->intval = 1;
		else
			val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = get_batt_uV(cm, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		fuel_gauge = power_supply_get_by_name(cm->desc->psy_fuel_gauge);
		if (!fuel_gauge) {
			ret = -ENODEV;
			break;
		}
		ret = power_supply_get_property(fuel_gauge,
				POWER_SUPPLY_PROP_CURRENT_NOW, val);
		break;
	case POWER_SUPPLY_PROP_TEMP:
	case POWER_SUPPLY_PROP_TEMP_AMBIENT:
		return cm_get_battery_temperature(cm, &val->intval);
	case POWER_SUPPLY_PROP_CAPACITY:
		if (!is_batt_present(cm)) {
			/* There is no battery. Assume 100% */
			val->intval = 100;
			break;
		}

		fuel_gauge = power_supply_get_by_name(cm->desc->psy_fuel_gauge);
		if (!fuel_gauge) {
			ret = -ENODEV;
			break;
		}

		ret = power_supply_get_property(fuel_gauge,
					POWER_SUPPLY_PROP_CAPACITY, val);
		if (ret)
			break;

		if (val->intval > 100) {
			val->intval = 100;
			break;
		}
		if (val->intval < 0)
			val->intval = 0;

		/* Do not adjust SOC when charging: voltage is overrated */
		if (is_charging(cm))
			break;

		/*
		 * If the capacity value is inconsistent, calibrate it base on
		 * the battery voltage values and the thresholds given as desc
		 */
		ret = get_batt_uV(cm, &uV);
		if (ret) {
			/* Voltage information not available. No calibration */
			ret = 0;
			break;
		}

		if (desc->fullbatt_uV > 0 && uV >= desc->fullbatt_uV &&
		    !is_charging(cm)) {
			val->intval = 100;
			break;
		}

		break;
	case POWER_SUPPLY_PROP_ONLINE:
		if (is_ext_pwr_online(cm))
			val->intval = 1;
		else
			val->intval = 0;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		if (is_full_charged(cm))
			val->intval = 1;
		else
			val->intval = 0;
		ret = 0;
		break;
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		if (is_charging(cm)) {
			fuel_gauge = power_supply_get_by_name(
					cm->desc->psy_fuel_gauge);
			if (!fuel_gauge) {
				ret = -ENODEV;
				break;
			}

			ret = power_supply_get_property(fuel_gauge,
						POWER_SUPPLY_PROP_CHARGE_NOW,
						val);
			if (ret) {
				val->intval = 1;
				ret = 0;
			} else {
				/* If CHARGE_NOW is supplied, use it */
				val->intval = (val->intval > 0) ?
						val->intval : 1;
			}
		} else {
			val->intval = 0;
		}
		break;
	default:
		return -EINVAL;
	}
	if (fuel_gauge)
		power_supply_put(fuel_gauge);
	return ret;
}