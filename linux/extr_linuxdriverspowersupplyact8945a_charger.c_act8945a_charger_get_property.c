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
union power_supply_propval {int /*<<< orphan*/  strval; int /*<<< orphan*/  intval; } ;
struct regmap {int dummy; } ;
struct power_supply {int dummy; } ;
struct act8945a_charger {struct regmap* regmap; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CAPACITY_LEVEL 135 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 134 
#define  POWER_SUPPLY_PROP_CURRENT_MAX 133 
#define  POWER_SUPPLY_PROP_HEALTH 132 
#define  POWER_SUPPLY_PROP_MANUFACTURER 131 
#define  POWER_SUPPLY_PROP_MODEL_NAME 130 
#define  POWER_SUPPLY_PROP_STATUS 129 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 128 
 int /*<<< orphan*/  POWER_SUPPLY_TECHNOLOGY_LION ; 
 int /*<<< orphan*/  act8945a_charger_manufacturer ; 
 int /*<<< orphan*/  act8945a_charger_model ; 
 int act8945a_get_battery_health (struct regmap*,int /*<<< orphan*/ *) ; 
 int act8945a_get_capacity_level (struct act8945a_charger*,struct regmap*,int /*<<< orphan*/ *) ; 
 int act8945a_get_charge_type (struct regmap*,int /*<<< orphan*/ *) ; 
 int act8945a_get_charger_state (struct regmap*,int /*<<< orphan*/ *) ; 
 int act8945a_get_current_max (struct act8945a_charger*,struct regmap*,int /*<<< orphan*/ *) ; 
 struct act8945a_charger* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int act8945a_charger_get_property(struct power_supply *psy,
					 enum power_supply_property prop,
					 union power_supply_propval *val)
{
	struct act8945a_charger *charger = power_supply_get_drvdata(psy);
	struct regmap *regmap = charger->regmap;
	int ret = 0;

	switch (prop) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = act8945a_get_charger_state(regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = act8945a_get_charge_type(regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		ret = act8945a_get_battery_health(regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		ret = act8945a_get_capacity_level(charger,
						  regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CURRENT_MAX:
		ret = act8945a_get_current_max(charger,
					       regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = act8945a_charger_model;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = act8945a_charger_manufacturer;
		break;
	default:
		return -EINVAL;
	}

	return ret;
}