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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  cv_active; int /*<<< orphan*/  charger_connected; int /*<<< orphan*/  charger_online; int /*<<< orphan*/  wd_expired; } ;
struct TYPE_3__ {int /*<<< orphan*/  ovv; int /*<<< orphan*/  main_thermal_prot; int /*<<< orphan*/  mainextchnotok; } ;
struct pm2xxx_charger {TYPE_2__ ac; TYPE_1__ flags; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_DEAD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_GOOD ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERHEAT ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_OVERVOLTAGE ; 
 int /*<<< orphan*/  POWER_SUPPLY_HEALTH_UNSPEC_FAILURE ; 
#define  POWER_SUPPLY_PROP_HEALTH 131 
#define  POWER_SUPPLY_PROP_ONLINE 130 
#define  POWER_SUPPLY_PROP_PRESENT 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_AVG 128 
 int /*<<< orphan*/  pm2xxx_charger_get_ac_cv (struct pm2xxx_charger*) ; 
 int /*<<< orphan*/  psy_to_ux500_charger (struct power_supply*) ; 
 struct pm2xxx_charger* to_pm2xxx_charger_ac_device_info (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm2xxx_charger_ac_get_property(struct power_supply *psy,
	enum power_supply_property psp,
	union power_supply_propval *val)
{
	struct pm2xxx_charger *pm2;

	pm2 = to_pm2xxx_charger_ac_device_info(psy_to_ux500_charger(psy));

	switch (psp) {
	case POWER_SUPPLY_PROP_HEALTH:
		if (pm2->flags.mainextchnotok)
			val->intval = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		else if (pm2->ac.wd_expired)
			val->intval = POWER_SUPPLY_HEALTH_DEAD;
		else if (pm2->flags.main_thermal_prot)
			val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		else if (pm2->flags.ovv)
			val->intval = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		else
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = pm2->ac.charger_online;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = pm2->ac.charger_connected;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_AVG:
		pm2->ac.cv_active = pm2xxx_charger_get_ac_cv(pm2);
		val->intval = pm2->ac.cv_active;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}