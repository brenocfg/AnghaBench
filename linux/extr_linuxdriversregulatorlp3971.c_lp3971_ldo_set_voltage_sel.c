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
struct lp3971 {int dummy; } ;

/* Variables and functions */
 unsigned int LDO_VOL_CONTR_MASK ; 
 unsigned int LDO_VOL_CONTR_SHIFT (int) ; 
 int LP3971_LDO1 ; 
 int /*<<< orphan*/  LP3971_LDO_VOL_CONTR_REG (int) ; 
 int lp3971_set_bits (struct lp3971*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct lp3971* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int lp3971_ldo_set_voltage_sel(struct regulator_dev *dev,
				      unsigned int selector)
{
	struct lp3971 *lp3971 = rdev_get_drvdata(dev);
	int ldo = rdev_get_id(dev) - LP3971_LDO1;

	return lp3971_set_bits(lp3971, LP3971_LDO_VOL_CONTR_REG(ldo),
			LDO_VOL_CONTR_MASK << LDO_VOL_CONTR_SHIFT(ldo),
			selector << LDO_VOL_CONTR_SHIFT(ldo));
}