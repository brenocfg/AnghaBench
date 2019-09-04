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
struct pwm_regulator_data {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  pwm_regulator_init_state (struct regulator_dev*) ; 
 struct pwm_regulator_data* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int pwm_regulator_get_voltage_sel(struct regulator_dev *rdev)
{
	struct pwm_regulator_data *drvdata = rdev_get_drvdata(rdev);

	if (drvdata->state < 0)
		pwm_regulator_init_state(rdev);

	return drvdata->state;
}