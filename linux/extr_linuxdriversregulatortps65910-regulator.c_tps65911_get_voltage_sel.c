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
struct tps65910_reg {unsigned int (* get_ctrl_reg ) (int) ;int /*<<< orphan*/  mfd; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LDO1_SEL_MASK ; 
 unsigned int LDO3_SEL_MASK ; 
 unsigned int LDO_SEL_MASK ; 
 unsigned int LDO_SEL_SHIFT ; 
#define  TPS65910_REG_VIO 136 
#define  TPS65911_REG_LDO1 135 
#define  TPS65911_REG_LDO2 134 
#define  TPS65911_REG_LDO3 133 
#define  TPS65911_REG_LDO4 132 
#define  TPS65911_REG_LDO5 131 
#define  TPS65911_REG_LDO6 130 
#define  TPS65911_REG_LDO7 129 
#define  TPS65911_REG_LDO8 128 
 struct tps65910_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 unsigned int stub1 (int) ; 
 int tps65910_reg_read (int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int tps65911_get_voltage_sel(struct regulator_dev *dev)
{
	struct tps65910_reg *pmic = rdev_get_drvdata(dev);
	int ret, id = rdev_get_id(dev);
	unsigned int value, reg;

	reg = pmic->get_ctrl_reg(id);

	ret = tps65910_reg_read(pmic->mfd, reg, &value);
	if (ret < 0)
		return ret;

	switch (id) {
	case TPS65911_REG_LDO1:
	case TPS65911_REG_LDO2:
	case TPS65911_REG_LDO4:
		value &= LDO1_SEL_MASK;
		value >>= LDO_SEL_SHIFT;
		break;
	case TPS65911_REG_LDO3:
	case TPS65911_REG_LDO5:
	case TPS65911_REG_LDO6:
	case TPS65911_REG_LDO7:
	case TPS65911_REG_LDO8:
		value &= LDO3_SEL_MASK;
		value >>= LDO_SEL_SHIFT;
		break;
	case TPS65910_REG_VIO:
		value &= LDO_SEL_MASK;
		value >>= LDO_SEL_SHIFT;
		break;
	default:
		return -EINVAL;
	}

	return value;
}