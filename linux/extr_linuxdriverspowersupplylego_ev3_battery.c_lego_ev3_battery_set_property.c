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
union power_supply_propval {int /*<<< orphan*/  intval; } ;
struct power_supply {int dummy; } ;
struct lego_ev3_battery {int technology; int v_max; int v_min; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_TECHNOLOGY 129 
#define  POWER_SUPPLY_TECHNOLOGY_NiMH 128 
 int POWER_SUPPLY_TECHNOLOGY_UNKNOWN ; 
 struct lego_ev3_battery* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int lego_ev3_battery_set_property(struct power_supply *psy,
					 enum power_supply_property psp,
					 const union power_supply_propval *val)
{
	struct lego_ev3_battery *batt = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		/*
		 * Only allow changing technology from Unknown to NiMH. Li-ion
		 * batteries are automatically detected and should not be
		 * overridden. Rechargeable AA batteries, on the other hand,
		 * cannot be automatically detected, and so must be manually
		 * specified. This should only be set once during system init,
		 * so there is no mechanism to go back to Unknown.
		 */
		if (batt->technology != POWER_SUPPLY_TECHNOLOGY_UNKNOWN)
			return -EINVAL;
		switch (val->intval) {
		case POWER_SUPPLY_TECHNOLOGY_NiMH:
			batt->technology = POWER_SUPPLY_TECHNOLOGY_NiMH;
			batt->v_max = 7800000;
			batt->v_min = 5400000;
			break;
		default:
			return -EINVAL;
		}
		break;
	default:
		return -EINVAL;
	}

	return 0;
}