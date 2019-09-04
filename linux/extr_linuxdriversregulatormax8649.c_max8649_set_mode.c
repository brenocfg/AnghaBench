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
struct regulator_dev {TYPE_1__* desc; } ;
struct max8649_regulator_info {int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsel_reg; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MAX8649_FORCE_PWM ; 
#define  REGULATOR_MODE_FAST 129 
#define  REGULATOR_MODE_NORMAL 128 
 struct max8649_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max8649_set_mode(struct regulator_dev *rdev, unsigned int mode)
{
	struct max8649_regulator_info *info = rdev_get_drvdata(rdev);

	switch (mode) {
	case REGULATOR_MODE_FAST:
		regmap_update_bits(info->regmap, rdev->desc->vsel_reg,
				   MAX8649_FORCE_PWM, MAX8649_FORCE_PWM);
		break;
	case REGULATOR_MODE_NORMAL:
		regmap_update_bits(info->regmap, rdev->desc->vsel_reg,
				   MAX8649_FORCE_PWM, 0);
		break;
	default:
		return -EINVAL;
	}
	return 0;
}