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
struct TYPE_2__ {int min_uV; int /*<<< orphan*/  uV_step; } ;
struct da903x_regulator_info {int max_uV; TYPE_1__ desc; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 scalar_t__ check_range (struct da903x_regulator_info*,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int,int) ; 
 struct da903x_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int da9030_map_ldo14_voltage(struct regulator_dev *rdev,
				    int min_uV, int max_uV)
{
	struct da903x_regulator_info *info = rdev_get_drvdata(rdev);
	int thresh, sel;

	if (check_range(info, min_uV, max_uV)) {
		pr_err("invalid voltage range (%d, %d) uV\n", min_uV, max_uV);
		return -EINVAL;
	}

	thresh = (info->max_uV + info->desc.min_uV) / 2;
	if (min_uV < thresh) {
		sel = DIV_ROUND_UP(thresh - min_uV, info->desc.uV_step);
		sel |= 0x4;
	} else {
		sel = DIV_ROUND_UP(min_uV - thresh, info->desc.uV_step);
	}

	return sel;
}