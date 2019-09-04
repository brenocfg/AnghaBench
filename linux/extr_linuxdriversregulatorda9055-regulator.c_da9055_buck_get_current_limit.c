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
struct TYPE_2__ {int mask; int shift; } ;
struct da9055_regulator_info {TYPE_1__ mode; } ;
struct da9055_regulator {int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_REG_BUCK_LIM ; 
 int* da9055_current_limits ; 
 int da9055_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9055_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da9055_buck_get_current_limit(struct regulator_dev *rdev)
{
	struct da9055_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9055_regulator_info *info = regulator->info;
	int ret;

	ret = da9055_reg_read(regulator->da9055, DA9055_REG_BUCK_LIM);
	if (ret < 0)
		return ret;

	ret &= info->mode.mask;
	return da9055_current_limits[ret >> info->mode.shift];
}