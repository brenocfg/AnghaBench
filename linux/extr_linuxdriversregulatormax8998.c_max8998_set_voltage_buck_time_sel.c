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
typedef  int u8 ;
struct voltage_map_desc {unsigned int step; } ;
struct regulator_dev {int dummy; } ;
struct max8998_data {TYPE_1__* iodev; } ;
struct i2c_client {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; struct i2c_client* i2c; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int EINVAL ; 
 int MAX8998_BUCK1 ; 
 int MAX8998_BUCK4 ; 
 int MAX8998_ENRAMP ; 
 int /*<<< orphan*/  MAX8998_REG_ONOFF4 ; 
 scalar_t__ TYPE_MAX8998 ; 
 struct voltage_map_desc** ldo_voltage_map ; 
 int max8998_read_reg (struct i2c_client*,int /*<<< orphan*/ ,int*) ; 
 struct max8998_data* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int max8998_set_voltage_buck_time_sel(struct regulator_dev *rdev,
					     unsigned int old_selector,
					     unsigned int new_selector)
{
	struct max8998_data *max8998 = rdev_get_drvdata(rdev);
	struct i2c_client *i2c = max8998->iodev->i2c;
	const struct voltage_map_desc *desc;
	int buck = rdev_get_id(rdev);
	u8 val = 0;
	int difference, ret;

	if (buck < MAX8998_BUCK1 || buck > MAX8998_BUCK4)
		return -EINVAL;

	desc = ldo_voltage_map[buck];

	/* Voltage stabilization */
	ret = max8998_read_reg(i2c, MAX8998_REG_ONOFF4, &val);
	if (ret)
		return ret;

	/* lp3974 hasn't got ENRAMP bit - ramp is assumed as true */
	/* MAX8998 has ENRAMP bit implemented, so test it*/
	if (max8998->iodev->type == TYPE_MAX8998 && !(val & MAX8998_ENRAMP))
		return 0;

	difference = (new_selector - old_selector) * desc->step / 1000;
	if (difference > 0)
		return DIV_ROUND_UP(difference, (val & 0x0f) + 1);

	return 0;
}