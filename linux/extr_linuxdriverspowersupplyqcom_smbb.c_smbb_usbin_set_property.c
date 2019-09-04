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
struct smbb_charger {int dummy; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int /*<<< orphan*/  ATTR_USBIN_IMAX ; 
 int EINVAL ; 
#define  POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT 128 
 struct smbb_charger* power_supply_get_drvdata (struct power_supply*) ; 
 int smbb_charger_attr_write (struct smbb_charger*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smbb_usbin_set_property(struct power_supply *psy,
		enum power_supply_property psp,
		const union power_supply_propval *val)
{
	struct smbb_charger *chg = power_supply_get_drvdata(psy);
	int rc;

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_CONTROL_LIMIT:
		rc = smbb_charger_attr_write(chg, ATTR_USBIN_IMAX,
				val->intval);
		break;
	default:
		rc = -EINVAL;
		break;
	}

	return rc;
}