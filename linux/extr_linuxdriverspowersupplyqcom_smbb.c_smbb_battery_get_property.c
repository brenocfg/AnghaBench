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
struct smbb_charger {unsigned long status; int* attr; int /*<<< orphan*/  statlock; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 size_t ATTR_BAT_IMAX ; 
 size_t ATTR_BAT_VMAX ; 
 int EINVAL ; 
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
 int POWER_SUPPLY_HEALTH_COLD ; 
 int POWER_SUPPLY_HEALTH_GOOD ; 
 int POWER_SUPPLY_HEALTH_OVERHEAT ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 135 
#define  POWER_SUPPLY_PROP_CURRENT_MAX 134 
#define  POWER_SUPPLY_PROP_HEALTH 133 
#define  POWER_SUPPLY_PROP_PRESENT 132 
#define  POWER_SUPPLY_PROP_STATUS 131 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 130 
#define  POWER_SUPPLY_PROP_VOLTAGE_MAX 129 
#define  POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN 128 
 int POWER_SUPPLY_STATUS_CHARGING ; 
 void* POWER_SUPPLY_STATUS_DISCHARGING ; 
 int POWER_SUPPLY_STATUS_FULL ; 
 int POWER_SUPPLY_TECHNOLOGY_LION ; 
 unsigned long STATUS_BAT_HOT ; 
 unsigned long STATUS_BAT_OK ; 
 unsigned long STATUS_BAT_PRESENT ; 
 unsigned long STATUS_CHG_DONE ; 
 unsigned long STATUS_CHG_FAST ; 
 unsigned long STATUS_CHG_GONE ; 
 unsigned long STATUS_CHG_TRKL ; 
 unsigned long STATUS_DCIN_VALID ; 
 unsigned long STATUS_USBIN_VALID ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct smbb_charger* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int smbb_battery_get_property(struct power_supply *psy,
		enum power_supply_property psp,
		union power_supply_propval *val)
{
	struct smbb_charger *chg = power_supply_get_drvdata(psy);
	unsigned long status;
	int rc = 0;

	mutex_lock(&chg->statlock);
	status = chg->status;
	mutex_unlock(&chg->statlock);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (status & STATUS_CHG_GONE)
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		else if (!(status & (STATUS_DCIN_VALID | STATUS_USBIN_VALID)))
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		else if (status & STATUS_CHG_DONE)
			val->intval = POWER_SUPPLY_STATUS_FULL;
		else if (!(status & STATUS_BAT_OK))
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		else if (status & (STATUS_CHG_FAST | STATUS_CHG_TRKL))
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else /* everything is ok for charging, but we are not... */
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		if (status & STATUS_BAT_OK)
			val->intval = POWER_SUPPLY_HEALTH_GOOD;
		else if (status & STATUS_BAT_HOT)
			val->intval = POWER_SUPPLY_HEALTH_OVERHEAT;
		else
			val->intval = POWER_SUPPLY_HEALTH_COLD;
		break;
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		if (status & STATUS_CHG_FAST)
			val->intval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		else if (status & STATUS_CHG_TRKL)
			val->intval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;
		else
			val->intval = POWER_SUPPLY_CHARGE_TYPE_NONE;
		break;
	case POWER_SUPPLY_PROP_PRESENT:
		val->intval = !!(status & STATUS_BAT_PRESENT);
		break;
	case POWER_SUPPLY_PROP_CURRENT_MAX:
		val->intval = chg->attr[ATTR_BAT_IMAX];
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
		val->intval = chg->attr[ATTR_BAT_VMAX];
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		/* this charger is a single-cell lithium-ion battery charger
		* only.  If you hook up some other technology, there will be
		* fireworks.
		*/
		val->intval = POWER_SUPPLY_TECHNOLOGY_LION;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MIN_DESIGN:
		val->intval = 3000000; /* single-cell li-ion low end */
		break;
	default:
		rc = -EINVAL;
		break;
	}

	return rc;
}