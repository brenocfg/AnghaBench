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
struct tps65910_reg {int (* get_ctrl_reg ) (int) ;int /*<<< orphan*/  mfd; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int LDO_ST_MODE_BIT ; 
 int LDO_ST_ON_BIT ; 
 unsigned int REGULATOR_MODE_IDLE ; 
 unsigned int REGULATOR_MODE_NORMAL ; 
 unsigned int REGULATOR_MODE_STANDBY ; 
 struct tps65910_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int stub1 (int) ; 
 int tps65910_reg_read (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static unsigned int tps65910_get_mode(struct regulator_dev *dev)
{
	struct tps65910_reg *pmic = rdev_get_drvdata(dev);
	int ret, reg, value, id = rdev_get_id(dev);

	reg = pmic->get_ctrl_reg(id);
	if (reg < 0)
		return reg;

	ret = tps65910_reg_read(pmic->mfd, reg, &value);
	if (ret < 0)
		return ret;

	if (!(value & LDO_ST_ON_BIT))
		return REGULATOR_MODE_STANDBY;
	else if (value & LDO_ST_MODE_BIT)
		return REGULATOR_MODE_IDLE;
	else
		return REGULATOR_MODE_NORMAL;
}