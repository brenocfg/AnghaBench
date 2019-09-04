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
typedef  int u8 ;
struct regmap {int dummy; } ;
struct max14577_charger {TYPE_2__* pdata; int /*<<< orphan*/  dev; TYPE_1__* max14577; } ;
struct TYPE_4__ {int ovp_uvolt; int /*<<< orphan*/  fast_charge_uamp; int /*<<< orphan*/  eoc_uamp; int /*<<< orphan*/  constant_uvolt; } ;
struct TYPE_3__ {struct regmap* regmap; } ;

/* Variables and functions */
 int CDETCTRL1_CHGDETEN_MASK ; 
 int CDETCTRL1_CHGDETEN_SHIFT ; 
 int CDETCTRL1_CHGTYPMAN_MASK ; 
 int CHGCTRL2_MBCHOSTEN_SHIFT ; 
 int CHGCTRL2_VCHGR_RC_SHIFT ; 
 int CHGCTRL6_AUTOSTOP_SHIFT ; 
 int CHGCTRL7_OTPCGHCVS_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  MAX14577_REG_CDETCTRL1 ; 
 int /*<<< orphan*/  MAX14577_REG_CHGCTRL2 ; 
 int /*<<< orphan*/  MAX14577_REG_CHGCTRL6 ; 
 int /*<<< orphan*/  MAX14577_REG_CHGCTRL7 ; 
 int /*<<< orphan*/  MAXIM_CHARGER_FAST_CHARGE_TIMER_DEFAULT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int max14577_init_constant_voltage (struct max14577_charger*,int /*<<< orphan*/ ) ; 
 int max14577_init_eoc (struct max14577_charger*,int /*<<< orphan*/ ) ; 
 int max14577_init_fast_charge (struct max14577_charger*,int /*<<< orphan*/ ) ; 
 int max14577_set_fast_charge_timer (struct max14577_charger*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max14577_update_reg (struct regmap*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  max14577_write_reg (struct regmap*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max14577_charger_reg_init(struct max14577_charger *chg)
{
	struct regmap *rmap = chg->max14577->regmap;
	u8 reg_data;
	int ret;

	/*
	 * Charger-Type Manual Detection, default off (set CHGTYPMAN to 0)
	 * Charger-Detection Enable, default on (set CHGDETEN to 1)
	 * Combined mask of CHGDETEN and CHGTYPMAN will zero the CHGTYPMAN bit
	 */
	reg_data = 0x1 << CDETCTRL1_CHGDETEN_SHIFT;
	max14577_update_reg(rmap, MAX14577_REG_CDETCTRL1,
			CDETCTRL1_CHGDETEN_MASK | CDETCTRL1_CHGTYPMAN_MASK,
			reg_data);

	/*
	 * Wall-Adapter Rapid Charge, default on
	 * Battery-Charger, default on
	 */
	reg_data = 0x1 << CHGCTRL2_VCHGR_RC_SHIFT;
	reg_data |= 0x1 << CHGCTRL2_MBCHOSTEN_SHIFT;
	max14577_write_reg(rmap, MAX14577_REG_CHGCTRL2, reg_data);

	/* Auto Charging Stop, default off */
	reg_data = 0x0 << CHGCTRL6_AUTOSTOP_SHIFT;
	max14577_write_reg(rmap, MAX14577_REG_CHGCTRL6, reg_data);

	ret = max14577_init_constant_voltage(chg, chg->pdata->constant_uvolt);
	if (ret)
		return ret;

	ret = max14577_init_eoc(chg, chg->pdata->eoc_uamp);
	if (ret)
		return ret;

	ret = max14577_init_fast_charge(chg, chg->pdata->fast_charge_uamp);
	if (ret)
		return ret;

	ret = max14577_set_fast_charge_timer(chg,
			MAXIM_CHARGER_FAST_CHARGE_TIMER_DEFAULT);
	if (ret)
		return ret;

	/* Initialize Overvoltage-Protection Threshold */
	switch (chg->pdata->ovp_uvolt) {
	case 7500000:
		reg_data = 0x0;
		break;
	case 6000000:
	case 6500000:
	case 7000000:
		reg_data = 0x1 + (chg->pdata->ovp_uvolt - 6000000) / 500000;
		break;
	default:
		dev_err(chg->dev, "Wrong value for OVP: %u\n",
				chg->pdata->ovp_uvolt);
		return -EINVAL;
	}
	reg_data <<= CHGCTRL7_OTPCGHCVS_SHIFT;
	max14577_write_reg(rmap, MAX14577_REG_CHGCTRL7, reg_data);

	return 0;
}