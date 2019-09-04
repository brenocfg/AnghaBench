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
typedef  int u16 ;
struct regulator_dev {int dummy; } ;
struct lp3971 {int dummy; } ;

/* Variables and functions */
 int BUCK_TARGET_VOL_MASK ; 
 int /*<<< orphan*/  LP3971_BUCK_TARGET_VOL1_REG (int) ; 
 int LP3971_DCDC1 ; 
 int lp3971_reg_read (struct lp3971*,int /*<<< orphan*/ ) ; 
 struct lp3971* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp3971_dcdc_get_voltage_sel(struct regulator_dev *dev)
{
	struct lp3971 *lp3971 = rdev_get_drvdata(dev);
	int buck = rdev_get_id(dev) - LP3971_DCDC1;
	u16 reg;

	reg = lp3971_reg_read(lp3971, LP3971_BUCK_TARGET_VOL1_REG(buck));
	reg &= BUCK_TARGET_VOL_MASK;

	return reg;
}