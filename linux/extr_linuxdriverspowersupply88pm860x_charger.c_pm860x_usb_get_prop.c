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
struct pm860x_charger_info {int /*<<< orphan*/  online; int /*<<< orphan*/  state; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FSM_FASTCHARGE ; 
 int /*<<< orphan*/  FSM_PRECHARGE ; 
#define  POWER_SUPPLY_PROP_ONLINE 129 
#define  POWER_SUPPLY_PROP_STATUS 128 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_CHARGING ; 
 int /*<<< orphan*/  POWER_SUPPLY_STATUS_DISCHARGING ; 
 struct pm860x_charger_info* power_supply_get_drvdata (struct power_supply*) ; 

__attribute__((used)) static int pm860x_usb_get_prop(struct power_supply *psy,
			       enum power_supply_property psp,
			       union power_supply_propval *val)
{
	struct pm860x_charger_info *info = power_supply_get_drvdata(psy);

	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		if (info->state == FSM_FASTCHARGE ||
				info->state == FSM_PRECHARGE)
			val->intval = POWER_SUPPLY_STATUS_CHARGING;
		else
			val->intval = POWER_SUPPLY_STATUS_DISCHARGING;
		break;
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = info->online;
		break;
	default:
		return -ENODEV;
	}
	return 0;
}