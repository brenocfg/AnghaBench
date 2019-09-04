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
struct rk808_regulator_data {struct gpio_desc** dvs_gpio; } ;
struct regulator_dev {int dummy; } ;
struct gpio_desc {int dummy; } ;

/* Variables and functions */
 struct rk808_regulator_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int regulator_set_voltage_time_sel (struct regulator_dev*,unsigned int,unsigned int) ; 

__attribute__((used)) static int rk808_buck1_2_set_voltage_time_sel(struct regulator_dev *rdev,
				       unsigned int old_selector,
				       unsigned int new_selector)
{
	struct rk808_regulator_data *pdata = rdev_get_drvdata(rdev);
	int id = rdev_get_id(rdev);
	struct gpio_desc *gpio = pdata->dvs_gpio[id];

	/* if there is no dvs1/2 pin, we don't need wait extra time here. */
	if (!gpio)
		return 0;

	return regulator_set_voltage_time_sel(rdev, old_selector, new_selector);
}