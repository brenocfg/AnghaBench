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
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int shift; int /*<<< orphan*/  mask; } ;
struct da9055_regulator_info {TYPE_1__ mode; } ;
struct da9055_regulator {int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DA9055_REG_BUCK_LIM ; 
 int EINVAL ; 
 int* da9055_current_limits ; 
 int da9055_reg_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct da9055_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da9055_buck_set_current_limit(struct regulator_dev *rdev, int min_uA,
					 int max_uA)
{
	struct da9055_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9055_regulator_info *info = regulator->info;
	int i;

	for (i = ARRAY_SIZE(da9055_current_limits) - 1; i >= 0; i--) {
		if ((min_uA <= da9055_current_limits[i]) &&
		    (da9055_current_limits[i] <= max_uA))
			return da9055_reg_update(regulator->da9055,
						 DA9055_REG_BUCK_LIM,
						 info->mode.mask,
						 i << info->mode.shift);
	}

	return -EINVAL;
}