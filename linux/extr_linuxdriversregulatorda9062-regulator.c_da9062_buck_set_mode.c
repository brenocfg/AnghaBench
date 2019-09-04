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
struct regulator_dev {int dummy; } ;
struct da9062_regulator {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 unsigned int BUCK_MODE_AUTO ; 
 unsigned int BUCK_MODE_SLEEP ; 
 unsigned int BUCK_MODE_SYNC ; 
 int EINVAL ; 
#define  REGULATOR_MODE_FAST 130 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 struct da9062_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int regmap_field_write (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int da9062_buck_set_mode(struct regulator_dev *rdev, unsigned mode)
{
	struct da9062_regulator *regl = rdev_get_drvdata(rdev);
	unsigned val;

	switch (mode) {
	case REGULATOR_MODE_FAST:
		val = BUCK_MODE_SYNC;
		break;
	case REGULATOR_MODE_NORMAL:
		val = BUCK_MODE_AUTO;
		break;
	case REGULATOR_MODE_STANDBY:
		val = BUCK_MODE_SLEEP;
		break;
	default:
		return -EINVAL;
	}

	return regmap_field_write(regl->mode, val);
}