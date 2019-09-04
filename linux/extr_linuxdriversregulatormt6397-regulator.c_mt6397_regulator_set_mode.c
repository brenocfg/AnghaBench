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
struct regulator_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  regmap; } ;
struct mt6397_regulator_info {int modeset_shift; int /*<<< orphan*/  modeset_mask; int /*<<< orphan*/  modeset_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int MT6397_BUCK_MODE_AUTO ; 
 int MT6397_BUCK_MODE_FORCE_PWM ; 
#define  REGULATOR_MODE_FAST 129 
#define  REGULATOR_MODE_NORMAL 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct mt6397_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt6397_regulator_set_mode(struct regulator_dev *rdev,
				     unsigned int mode)
{
	struct mt6397_regulator_info *info = rdev_get_drvdata(rdev);
	int ret, val;

	switch (mode) {
	case REGULATOR_MODE_FAST:
		val = MT6397_BUCK_MODE_FORCE_PWM;
		break;
	case REGULATOR_MODE_NORMAL:
		val = MT6397_BUCK_MODE_AUTO;
		break;
	default:
		ret = -EINVAL;
		goto err_mode;
	}

	dev_dbg(&rdev->dev, "mt6397 buck set_mode %#x, %#x, %#x, %#x\n",
		info->modeset_reg, info->modeset_mask,
		info->modeset_shift, val);

	val <<= info->modeset_shift;
	ret = regmap_update_bits(rdev->regmap, info->modeset_reg,
				 info->modeset_mask, val);
err_mode:
	if (ret != 0) {
		dev_err(&rdev->dev,
			"Failed to set mt6397 buck mode: %d\n", ret);
		return ret;
	}

	return 0;
}