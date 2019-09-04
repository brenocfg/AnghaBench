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
typedef  int /*<<< orphan*/  u32 ;
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct hi6421_regulator_info {int /*<<< orphan*/  mode_mask; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_reg; } ;

/* Variables and functions */
 int EINVAL ; 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 struct hi6421_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hi6421_regulator_buck_set_mode(struct regulator_dev *rdev,
						unsigned int mode)
{
	struct hi6421_regulator_info *info = rdev_get_drvdata(rdev);
	u32 new_mode;

	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		new_mode = 0;
		break;
	case REGULATOR_MODE_STANDBY:
		new_mode = info->mode_mask;
		break;
	default:
		return -EINVAL;
	}

	/* set mode */
	regmap_update_bits(rdev->regmap, rdev->desc->enable_reg,
			   info->mode_mask, new_mode);

	return 0;
}