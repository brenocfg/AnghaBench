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
struct smb347_charger {int /*<<< orphan*/  regmap; TYPE_1__* pdata; } ;
struct TYPE_2__ {scalar_t__ termination_current; scalar_t__ pre_charge_current; scalar_t__ max_charge_current; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CFG_CHARGE_CURRENT ; 
 int /*<<< orphan*/  CFG_CHARGE_CURRENT_FCC_MASK ; 
 int CFG_CHARGE_CURRENT_FCC_SHIFT ; 
 int /*<<< orphan*/  CFG_CHARGE_CURRENT_PCC_MASK ; 
 int CFG_CHARGE_CURRENT_PCC_SHIFT ; 
 int /*<<< orphan*/  CFG_CHARGE_CURRENT_TC_MASK ; 
 int current_to_hw (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fcc_tbl ; 
 int /*<<< orphan*/  pcc_tbl ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tc_tbl ; 

__attribute__((used)) static int smb347_set_charge_current(struct smb347_charger *smb)
{
	int ret;

	if (smb->pdata->max_charge_current) {
		ret = current_to_hw(fcc_tbl, ARRAY_SIZE(fcc_tbl),
				    smb->pdata->max_charge_current);
		if (ret < 0)
			return ret;

		ret = regmap_update_bits(smb->regmap, CFG_CHARGE_CURRENT,
					 CFG_CHARGE_CURRENT_FCC_MASK,
					 ret << CFG_CHARGE_CURRENT_FCC_SHIFT);
		if (ret < 0)
			return ret;
	}

	if (smb->pdata->pre_charge_current) {
		ret = current_to_hw(pcc_tbl, ARRAY_SIZE(pcc_tbl),
				    smb->pdata->pre_charge_current);
		if (ret < 0)
			return ret;

		ret = regmap_update_bits(smb->regmap, CFG_CHARGE_CURRENT,
					 CFG_CHARGE_CURRENT_PCC_MASK,
					 ret << CFG_CHARGE_CURRENT_PCC_SHIFT);
		if (ret < 0)
			return ret;
	}

	if (smb->pdata->termination_current) {
		ret = current_to_hw(tc_tbl, ARRAY_SIZE(tc_tbl),
				    smb->pdata->termination_current);
		if (ret < 0)
			return ret;

		ret = regmap_update_bits(smb->regmap, CFG_CHARGE_CURRENT,
					 CFG_CHARGE_CURRENT_TC_MASK, ret);
		if (ret < 0)
			return ret;
	}

	return 0;
}