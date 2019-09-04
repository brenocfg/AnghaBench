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
typedef  int /*<<< orphan*/  u8 ;
struct regulator_dev {int dummy; } ;
struct max77620_regulator_pdata {unsigned int current_mode; } ;
struct max77620_regulator_info {scalar_t__ type; int cfg_addr; } ;
struct max77620_regulator {int* enable_power_mode; int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; struct max77620_regulator_pdata* reg_pdata; struct max77620_regulator_info** rinfo; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX77620_POWER_MODE_LPM ; 
 int MAX77620_POWER_MODE_NORMAL ; 
 scalar_t__ MAX77620_REGULATOR_TYPE_SD ; 
 int /*<<< orphan*/  MAX77620_SD_FPWM_MASK ; 
#define  REGULATOR_MODE_FAST 130 
#define  REGULATOR_MODE_IDLE 129 
#define  REGULATOR_MODE_NORMAL 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int max77620_regulator_set_power_mode (struct max77620_regulator*,int,int) ; 
 struct max77620_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max77620_regulator_set_mode(struct regulator_dev *rdev,
				       unsigned int mode)
{
	struct max77620_regulator *pmic = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	struct max77620_regulator_info *rinfo = pmic->rinfo[id];
	struct max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];
	bool fpwm = false;
	int power_mode;
	int ret;
	u8 val;

	switch (mode) {
	case REGULATOR_MODE_FAST:
		fpwm = true;
		power_mode = MAX77620_POWER_MODE_NORMAL;
		break;

	case REGULATOR_MODE_NORMAL:
		power_mode = MAX77620_POWER_MODE_NORMAL;
		break;

	case REGULATOR_MODE_IDLE:
		power_mode = MAX77620_POWER_MODE_LPM;
		break;

	default:
		dev_err(pmic->dev, "Regulator %d mode %d is invalid\n",
			id, mode);
		return -EINVAL;
	}

	if (rinfo->type != MAX77620_REGULATOR_TYPE_SD)
		goto skip_fpwm;

	val = (fpwm) ? MAX77620_SD_FPWM_MASK : 0;
	ret = regmap_update_bits(pmic->rmap, rinfo->cfg_addr,
				 MAX77620_SD_FPWM_MASK, val);
	if (ret < 0) {
		dev_err(pmic->dev, "Reg 0x%02x update failed: %d\n",
			rinfo->cfg_addr, ret);
		return ret;
	}
	rpdata->current_mode = mode;

skip_fpwm:
	ret = max77620_regulator_set_power_mode(pmic, power_mode, id);
	if (ret < 0)
		return ret;

	pmic->enable_power_mode[id] = power_mode;

	return 0;
}