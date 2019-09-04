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
struct TYPE_2__ {int mask; int shift; int /*<<< orphan*/  reg; } ;
struct da9055_regulator_info {TYPE_1__ mode; } ;
struct da9055_regulator {int /*<<< orphan*/  da9055; struct da9055_regulator_info* info; } ;

/* Variables and functions */
#define  DA9055_BUCK_MODE_AUTO 130 
#define  DA9055_BUCK_MODE_SLEEP 129 
#define  DA9055_BUCK_MODE_SYNC 128 
 int REGULATOR_MODE_FAST ; 
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 int da9055_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct da9055_regulator* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static unsigned int da9055_buck_get_mode(struct regulator_dev *rdev)
{
	struct da9055_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9055_regulator_info *info = regulator->info;
	int ret, mode = 0;

	ret = da9055_reg_read(regulator->da9055, info->mode.reg);
	if (ret < 0)
		return ret;

	switch ((ret & info->mode.mask) >> info->mode.shift) {
	case DA9055_BUCK_MODE_SYNC:
		mode = REGULATOR_MODE_FAST;
		break;
	case DA9055_BUCK_MODE_AUTO:
		mode = REGULATOR_MODE_NORMAL;
		break;
	case DA9055_BUCK_MODE_SLEEP:
		mode = REGULATOR_MODE_STANDBY;
		break;
	}

	return mode;
}