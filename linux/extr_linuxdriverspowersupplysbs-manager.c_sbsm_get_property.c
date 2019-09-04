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
struct sbsm_data {int /*<<< orphan*/  client; int /*<<< orphan*/  is_ltc1760; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int POWER_SUPPLY_CHARGE_TYPE_FAST ; 
 int POWER_SUPPLY_CHARGE_TYPE_NONE ; 
 int POWER_SUPPLY_CHARGE_TYPE_TRICKLE ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 129 
#define  POWER_SUPPLY_PROP_ONLINE 128 
 int SBSM_BIT_AC_PRESENT ; 
 int SBSM_BIT_TURBO ; 
 int /*<<< orphan*/  SBSM_CMD_BATSYSSTATE ; 
 int /*<<< orphan*/  SBSM_CMD_BATSYSSTATECONT ; 
 int /*<<< orphan*/  SBSM_CMD_LTC ; 
 int SBSM_MASK_CHARGE_BAT ; 
 struct sbsm_data* power_supply_get_drvdata (struct power_supply*) ; 
 int sbsm_read_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbsm_get_property(struct power_supply *psy,
			     enum power_supply_property psp,
			     union power_supply_propval *val)
{
	struct sbsm_data *data = power_supply_get_drvdata(psy);
	int regval = 0;

	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		regval = sbsm_read_word(data->client, SBSM_CMD_BATSYSSTATECONT);
		if (regval < 0)
			return regval;
		val->intval = !!(regval & SBSM_BIT_AC_PRESENT);
		break;

	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		regval = sbsm_read_word(data->client, SBSM_CMD_BATSYSSTATE);
		if (regval < 0)
			return regval;

		if ((regval & SBSM_MASK_CHARGE_BAT) == 0) {
			val->intval = POWER_SUPPLY_CHARGE_TYPE_NONE;
			return 0;
		}
		val->intval = POWER_SUPPLY_CHARGE_TYPE_TRICKLE;

		if (data->is_ltc1760) {
			/* charge mode fast if turbo is active */
			regval = sbsm_read_word(data->client, SBSM_CMD_LTC);
			if (regval < 0)
				return regval;
			else if (regval & SBSM_BIT_TURBO)
				val->intval = POWER_SUPPLY_CHARGE_TYPE_FAST;
		}
		break;

	default:
		return -EINVAL;
	}

	return 0;
}