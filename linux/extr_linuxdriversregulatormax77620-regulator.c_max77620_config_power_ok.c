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
typedef  int /*<<< orphan*/  u8 ;
struct max77620_regulator_pdata {int /*<<< orphan*/  power_ok; } ;
struct max77620_regulator_info {int /*<<< orphan*/  cfg_addr; int /*<<< orphan*/  type; } ;
struct max77620_regulator {TYPE_1__* dev; int /*<<< orphan*/  rmap; struct max77620_regulator_info** rinfo; struct max77620_regulator_pdata* reg_pdata; } ;
struct max77620_chip {int chip_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
#define  MAX20024 128 
 int /*<<< orphan*/  MAX20024_LDO_CFG2_MPOK_MASK ; 
 int /*<<< orphan*/  MAX20024_SD_CFG1_MPOK_MASK ; 
 int /*<<< orphan*/  MAX77620_REGULATOR_TYPE_SD ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,int /*<<< orphan*/ ,int) ; 
 struct max77620_chip* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77620_config_power_ok(struct max77620_regulator *pmic, int id)
{
	struct max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];
	struct max77620_regulator_info *rinfo = pmic->rinfo[id];
	struct max77620_chip *chip = dev_get_drvdata(pmic->dev->parent);
	u8 val, mask;
	int ret;

	switch (chip->chip_id) {
	case MAX20024:
		if (rpdata->power_ok >= 0) {
			if (rinfo->type == MAX77620_REGULATOR_TYPE_SD)
				mask = MAX20024_SD_CFG1_MPOK_MASK;
			else
				mask = MAX20024_LDO_CFG2_MPOK_MASK;

			val = rpdata->power_ok ? mask : 0;

			ret = regmap_update_bits(pmic->rmap, rinfo->cfg_addr,
						 mask, val);
			if (ret < 0) {
				dev_err(pmic->dev, "Reg 0x%02x update failed %d\n",
					rinfo->cfg_addr, ret);
				return ret;
			}
		}
		break;

	default:
		break;
	}

	return 0;
}