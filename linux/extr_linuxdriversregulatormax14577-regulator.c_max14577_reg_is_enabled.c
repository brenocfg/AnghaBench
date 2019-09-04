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

/* Variables and functions */
 int CHGCTRL2_MBCHOSTEN_MASK ; 
 int EINVAL ; 
#define  MAX14577_CHARGER 128 
 int /*<<< orphan*/  MAX14577_CHG_REG_CHG_CTRL2 ; 
 int /*<<< orphan*/  MAX14577_CHG_REG_STATUS3 ; 
 int STATUS3_CGMBC_MASK ; 
 int /*<<< orphan*/  max14577_read_reg (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int max14577_reg_is_enabled(struct regulator_dev *rdev)
{
	int rid = rdev_get_id(rdev);
	struct regmap *rmap = rdev->regmap;
	u8 reg_data;

	switch (rid) {
	case MAX14577_CHARGER:
		max14577_read_reg(rmap, MAX14577_CHG_REG_CHG_CTRL2, &reg_data);
		if ((reg_data & CHGCTRL2_MBCHOSTEN_MASK) == 0)
			return 0;
		max14577_read_reg(rmap, MAX14577_CHG_REG_STATUS3, &reg_data);
		if ((reg_data & STATUS3_CGMBC_MASK) == 0)
			return 0;
		/* MBCHOSTEN and CGMBC are on */
		return 1;
	default:
		return -EINVAL;
	}
}