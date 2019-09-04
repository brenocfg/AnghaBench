#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union power_supply_propval {int intval; } ;
struct power_supply {int dummy; } ;
struct TYPE_6__ {int charger_online; int charger_connected; int charger_voltage; int cv_active; int charger_current; int /*<<< orphan*/  wd_expired; } ;
struct TYPE_5__ {int /*<<< orphan*/  main_thermal_prot; int /*<<< orphan*/  mainextchnotok; } ;
struct TYPE_4__ {int /*<<< orphan*/  wd_expired; } ;
struct ab8500_charger {TYPE_3__ ac; TYPE_2__ flags; TYPE_1__ usb; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_HEALTH_DEAD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
#define  POWER_SUPPLY_PROP_CURRENT_NOW 133 
#define  POWER_SUPPLY_PROP_HEALTH 132 
#define  POWER_SUPPLY_PROP_ONLINE 131 
#define  POWER_SUPPLY_PROP_PRESENT 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_NOW 128 
 int ab8500_charger_ac_cv (struct ab8500_charger*) ; 
 int ab8500_charger_get_ac_current (struct ab8500_charger*) ; 
 int ab8500_charger_get_ac_voltage (struct ab8500_charger*) ; 
 int /*<<< orphan*/  psy_to_ux500_charger (struct power_supply*) ; 
 struct ab8500_charger* to_ab8500_charger_ac_device_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab8500_charger_ac_get_property(struct power_supply *psy,
	enum power_supply_property psp,
	union power_supply_propval *val)
{
	struct ab8500_charger *di;
	int ret;

	di = to_ab8500_charger_ac_device_info(psy_to_ux500_charger(psy));

	switch (psp) {
	case POWER_SUPPLY_PROP_HEALTH:
		if (di->flags.mainextchnotok)
			val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		else if (di->ac.wd_expired || di->usb.wd_expired)
			val->intval = POWER_SUPPLY_HEALTH_DEAD;
		else if (di->flags.main_thermal_prot)
			val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		else
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = di->ac.charger_online;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = di->ac.charger_connected;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		ret = ab8500_charger_get_ac_voltage(di);
		if (ret >= 0)
			di->ac.charger_voltage = ret;
		/* On error, use previous value */
		val->intval = di->ac.charger_voltage * 1000;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		/*
		 * This property is used to indicate when CV mode is entered
		 * for the AC charger
		 */
		di->ac.cv_active = ab8500_charger_ac_cv(di);
		val->intval = di->ac.cv_active;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		ret = ab8500_charger_get_ac_current(di);
		if (ret >= 0)
			di->ac.charger_current = ret;
		val->intval = di->ac.charger_current * 1000;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}