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
struct mt6397_regulator_info {int modeset_mask; int modeset_shift; int /*<<< orphan*/  modeset_reg; } ;

/* Variables and functions */
 unsigned int EINVAL ; 
#define  MT6397_BUCK_MODE_AUTO 129 
#define  MT6397_BUCK_MODE_FORCE_PWM 128 
 unsigned int REGULATOR_MODE_FAST ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct mt6397_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static unsigned int mt6397_regulator_get_mode(struct regulator_dev *rdev)
{
	struct mt6397_regulator_info *info = rdev_get_drvdata(rdev);
	int ret, regval;

	ret = regmap_read(rdev->regmap, info->modeset_reg, &regval);
	if (ret != 0) {
		dev_err(&rdev->dev,
			"Failed to get mt6397 buck mode: %d\n", ret);
		return ret;
	}

	switch ((regval & info->modeset_mask) >> info->modeset_shift) {
	case MT6397_BUCK_MODE_AUTO:
		return REGULATOR_MODE_NORMAL;
	case MT6397_BUCK_MODE_FORCE_PWM:
		return REGULATOR_MODE_FAST;
	default:
		return -EINVAL;
	}
}