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
typedef  int u8 ;
struct regulator_dev {struct regmap* regmap; } ;
struct regmap {int dummy; } ;
struct maxim_charger_current {int min; int high_start; int high_step; } ;
struct max14577 {size_t dev_type; } ;

/* Variables and functions */
 int CHGCTRL4_MBCICHWRCH_MASK ; 
 int CHGCTRL4_MBCICHWRCH_SHIFT ; 
 int CHGCTRL4_MBCICHWRCL_MASK ; 
 int EINVAL ; 
 scalar_t__ MAX14577_CHARGER ; 
 int /*<<< orphan*/  MAX14577_CHG_REG_CHG_CTRL4 ; 
 int /*<<< orphan*/  max14577_read_reg (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 struct maxim_charger_current* maxim_charger_currents ; 
 struct max14577* rdev_get_drvdata (struct regulator_dev*) ; 
 scalar_t__ rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int max14577_reg_get_current_limit(struct regulator_dev *rdev)
{
	u8 reg_data;
	struct regmap *rmap = rdev->regmap;
	struct max14577 *max14577 = rdev_get_drvdata(rdev);
	const struct maxim_charger_current *limits =
		&maxim_charger_currents[max14577->dev_type];

	if (rdev_get_id(rdev) != MAX14577_CHARGER)
		return -EINVAL;

	max14577_read_reg(rmap, MAX14577_CHG_REG_CHG_CTRL4, &reg_data);

	if ((reg_data & CHGCTRL4_MBCICHWRCL_MASK) == 0)
		return limits->min;

	reg_data = ((reg_data & CHGCTRL4_MBCICHWRCH_MASK) >>
			CHGCTRL4_MBCICHWRCH_SHIFT);
	return limits->high_start + reg_data * limits->high_step;
}