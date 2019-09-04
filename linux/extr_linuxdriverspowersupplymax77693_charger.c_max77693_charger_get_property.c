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
union power_supply_propval {int /*<<< orphan*/  strval; int /*<<< orphan*/  intval; } ;
struct regmap {int dummy; } ;
struct power_supply {int dummy; } ;
struct max77693_charger {TYPE_1__* max77693; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;
struct TYPE_2__ {struct regmap* regmap; } ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 134 
#define  POWER_SUPPLY_PROP_HEALTH 133 
#define  POWER_SUPPLY_PROP_MANUFACTURER 132 
#define  POWER_SUPPLY_PROP_MODEL_NAME 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_PRESENT 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int /*<<< orphan*/  max77693_charger_manufacturer ; 
 int /*<<< orphan*/  max77693_charger_model ; 
 int max77693_get_battery_health (struct regmap*,int /*<<< orphan*/ *) ; 
 int max77693_get_charge_type (struct regmap*,int /*<<< orphan*/ *) ; 
 int max77693_get_charger_state (struct regmap*,int /*<<< orphan*/ *) ; 
 int max77693_get_online (struct regmap*,int /*<<< orphan*/ *) ; 
 int max77693_get_present (struct regmap*,int /*<<< orphan*/ *) ; 
 struct max77693_charger* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int max77693_charger_get_property(struct power_supply *psy,
			    enum power_supply_property psp,
			    union power_supply_propval *val)
{
	struct max77693_charger *chg = power_supply_get_drvdata(psy);
	struct regmap *regmap = chg->max77693->regmap;
	int ret = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		ret = max77693_get_charger_state(regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		ret = max77693_get_charge_type(regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		ret = max77693_get_battery_health(regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		ret = max77693_get_present(regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		ret = max77693_get_online(regmap, &val->intval);
		break;
	case POWER_SUPPLY_PROP_MODEL_NAME:
		val->strval = max77693_charger_model;
		break;
	case POWER_SUPPLY_PROP_MANUFACTURER:
		val->strval = max77693_charger_manufacturer;
		break;
	default:
		return -EINVAL;
	}

	return ret;
}