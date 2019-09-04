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
typedef  union power_supply_propval {int dummy; } power_supply_propval ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct power_supply {TYPE_1__ dev; } ;
struct da9150_charger {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CURRENT_AVG 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_TEMP 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int da9150_charger_ibus_current_avg (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_supply_online (struct da9150_charger*,struct power_supply*,union power_supply_propval*) ; 
 int da9150_charger_tjunc_temp (struct da9150_charger*,union power_supply_propval*) ; 
 int da9150_charger_vbus_voltage_now (struct da9150_charger*,union power_supply_propval*) ; 
 struct da9150_charger* dev_get_drvdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int da9150_charger_get_prop(struct power_supply *psy,
				   enum power_supply_property psp,
				   union power_supply_propval *val)
{
	struct da9150_charger *charger = dev_get_drvdata(psy->dev.parent);
	int ret;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		ret = da9150_charger_supply_online(charger, psy, val);
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = da9150_charger_vbus_voltage_now(charger, val);
		break;
	case POWER_SUPPLY_PROP_CURRENT_AVG:
		ret = da9150_charger_ibus_current_avg(charger, val);
		break;
	case POWER_SUPPLY_PROP_TEMP:
		ret = da9150_charger_tjunc_temp(charger, val);
		break;
	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}