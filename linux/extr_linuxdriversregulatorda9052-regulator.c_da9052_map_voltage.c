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
struct da9052_regulator_info {int min_uV; int /*<<< orphan*/  step_uV; } ;
struct da9052_regulator {TYPE_1__* da9052; struct da9052_regulator_info* info; } ;
struct TYPE_2__ {scalar_t__ chip_id; } ;

/* Variables and functions */
 scalar_t__ DA9052 ; 
 int /*<<< orphan*/  DA9052_BUCK_PERI_3uV_STEP ; 
 int DA9052_BUCK_PERI_REG_MAP_UPTO_3uV ; 
 int DA9052_CONST_3uV ; 
 int DA9052_ID_BUCK4 ; 
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int da9052_list_voltage (struct regulator_dev*,int) ; 
 struct da9052_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int verify_range (struct da9052_regulator_info*,int,int) ; 

__attribute__((used)) static int da9052_map_voltage(struct regulator_dev *rdev,
			      int min_uV, int max_uV)
{
	struct da9052_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9052_regulator_info *info = regulator->info;
	int id = rdev_get_id(rdev);
	int ret, sel;

	ret = verify_range(info, min_uV, max_uV);
	if (ret < 0)
		return ret;

	if (min_uV < info->min_uV)
		min_uV = info->min_uV;

	if ((id == DA9052_ID_BUCK4) && (regulator->da9052->chip_id == DA9052)
		&& (min_uV >= DA9052_CONST_3uV)) {
			sel = DA9052_BUCK_PERI_REG_MAP_UPTO_3uV +
			      DIV_ROUND_UP(min_uV - DA9052_CONST_3uV,
					   DA9052_BUCK_PERI_3uV_STEP);
	} else {
		sel = DIV_ROUND_UP(min_uV - info->min_uV, info->step_uV);
	}

	ret = da9052_list_voltage(rdev, sel);
	if (ret < 0)
		return ret;

	return sel;
}