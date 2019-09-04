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
struct ab8500_ext_regulator_info {scalar_t__ update_val; scalar_t__ update_val_hp; scalar_t__ update_val_lp; } ;

/* Variables and functions */
 unsigned int EINVAL ; 
 int REGULATOR_MODE_IDLE ; 
 int REGULATOR_MODE_NORMAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rdev_get_dev (struct regulator_dev*) ; 
 struct ab8500_ext_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static unsigned int ab8500_ext_regulator_get_mode(struct regulator_dev *rdev)
{
	struct ab8500_ext_regulator_info *info = rdev_get_drvdata(rdev);
	int ret;

	if (info == NULL) {
		dev_err(rdev_get_dev(rdev), "regulator info null pointer\n");
		return -EINVAL;
	}

	if (info->update_val == info->update_val_hp)
		ret = REGULATOR_MODE_NORMAL;
	else if (info->update_val == info->update_val_lp)
		ret = REGULATOR_MODE_IDLE;
	else
		ret = -EINVAL;

	return ret;
}