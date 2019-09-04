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
struct da9052_regulator_info {unsigned int step_uV; } ;
struct da9052_regulator {struct da9052_regulator_info* info; } ;

/* Variables and functions */
#define  DA9052_ID_BUCK1 132 
#define  DA9052_ID_BUCK2 131 
#define  DA9052_ID_BUCK3 130 
#define  DA9052_ID_LDO2 129 
#define  DA9052_ID_LDO3 128 
 struct da9052_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int da9052_regulator_set_voltage_time_sel(struct regulator_dev *rdev,
						 unsigned int old_sel,
						 unsigned int new_sel)
{
	struct da9052_regulator *regulator = rdev_get_drvdata(rdev);
	struct da9052_regulator_info *info = regulator->info;
	int id = rdev_get_id(rdev);
	int ret = 0;

	/* The DVC controlled LDOs and DCDCs ramp with 6.25mV/µs after enabling
	 * the activate bit.
	 */
	switch (id) {
	case DA9052_ID_BUCK1:
	case DA9052_ID_BUCK2:
	case DA9052_ID_BUCK3:
	case DA9052_ID_LDO2:
	case DA9052_ID_LDO3:
		ret = (new_sel - old_sel) * info->step_uV / 6250;
		break;
	}

	return ret;
}