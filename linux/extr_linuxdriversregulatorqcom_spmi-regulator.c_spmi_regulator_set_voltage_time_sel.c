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
struct spmi_voltage_range {int step_uV; } ;
struct spmi_regulator {int /*<<< orphan*/  slew_rate; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int abs (unsigned int) ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 struct spmi_voltage_range* spmi_regulator_find_range (struct spmi_regulator*) ; 

__attribute__((used)) static int spmi_regulator_set_voltage_time_sel(struct regulator_dev *rdev,
		unsigned int old_selector, unsigned int new_selector)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	const struct spmi_voltage_range *range;
	int diff_uV;

	range = spmi_regulator_find_range(vreg);
	if (!range)
		return -EINVAL;

	diff_uV = abs(new_selector - old_selector) * range->step_uV;

	return DIV_ROUND_UP(diff_uV, vreg->slew_rate);
}