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
typedef  int /*<<< orphan*/  u16 ;
struct sbsm_data {int /*<<< orphan*/  client; int /*<<< orphan*/  is_ltc1760; } ;
struct power_supply {int dummy; } ;
typedef  enum power_supply_property { ____Placeholder_power_supply_property } power_supply_property ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  POWER_SUPPLY_CHARGE_TYPE_FAST ; 
#define  POWER_SUPPLY_PROP_CHARGE_TYPE 128 
 int /*<<< orphan*/  SBSM_BIT_TURBO ; 
 int /*<<< orphan*/  SBSM_CMD_LTC ; 
 struct sbsm_data* power_supply_get_drvdata (struct power_supply*) ; 
 int sbsm_write_word (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sbsm_set_property(struct power_supply *psy,
			     enum power_supply_property psp,
			     const union power_supply_propval *val)
{
	struct sbsm_data *data = power_supply_get_drvdata(psy);
	int ret = -EINVAL;
	u16 regval;

	switch (psp) {
	case POWER_SUPPLY_PROP_CHARGE_TYPE:
		/* write 1 to TURBO if type fast is given */
		if (!data->is_ltc1760)
			break;
		regval = val->intval ==
			 POWER_SUPPLY_CHARGE_TYPE_FAST ? SBSM_BIT_TURBO : 0;
		ret = sbsm_write_word(data->client, SBSM_CMD_LTC, regval);
		break;

	default:
		break;
	}

	return ret;
}