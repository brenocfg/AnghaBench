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
struct max77620_regulator_pdata {scalar_t__ ramp_rate_setting; } ;
struct max77620_regulator {struct max77620_regulator_pdata* reg_pdata; } ;

/* Variables and functions */
 int max77620_set_slew_rate (struct max77620_regulator*,int,int) ; 
 struct max77620_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int max77620_regulator_set_ramp_delay(struct regulator_dev *rdev,
					     int ramp_delay)
{
	struct max77620_regulator *pmic = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	struct max77620_regulator_pdata *rpdata = &pmic->reg_pdata[id];

	/* Device specific ramp rate setting tells that platform has
	 * different ramp rate from advertised value. In this case,
	 * do not configure anything and just return success.
	 */
	if (rpdata->ramp_rate_setting)
		return 0;

	return max77620_set_slew_rate(pmic, id, ramp_delay);
}