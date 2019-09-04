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
 int /*<<< orphan*/  BBCH_BBSEL_MASK ; 
 unsigned int BBCH_BBSEL_SHIFT ; 
 int EINVAL ; 
 int /*<<< orphan*/  LDO_SEL_MASK ; 
 unsigned int LDO_SEL_SHIFT ; 
#define  TPS65910_REG_VAUX1 137 
#define  TPS65910_REG_VAUX2 136 
#define  TPS65910_REG_VAUX33 135 
#define  TPS65910_REG_VBB 134 
#define  TPS65910_REG_VDAC 133 
#define  TPS65910_REG_VDIG1 132 
#define  TPS65910_REG_VDIG2 131 
#define  TPS65910_REG_VIO 130 
#define  TPS65910_REG_VMMC 129 
#define  TPS65910_REG_VPLL 128 
 struct tps65910_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int stub1 (int) ; 
 int tps65910_reg_update_bits (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int tps65910_set_voltage_sel(struct regulator_dev *dev,
				    unsigned selector)
{
	struct tps65910_reg *pmic = rdev_get_drvdata(dev);
	int reg, id = rdev_get_id(dev);

	reg = pmic->get_ctrl_reg(id);
	if (reg < 0)
		return reg;

	switch (id) {
	case TPS65910_REG_VIO:
	case TPS65910_REG_VDIG1:
	case TPS65910_REG_VDIG2:
	case TPS65910_REG_VPLL:
	case TPS65910_REG_VDAC:
	case TPS65910_REG_VAUX1:
	case TPS65910_REG_VAUX2:
	case TPS65910_REG_VAUX33:
	case TPS65910_REG_VMMC:
		return tps65910_reg_update_bits(pmic->mfd, reg, LDO_SEL_MASK,
						selector << LDO_SEL_SHIFT);
	case TPS65910_REG_VBB:
		return tps65910_reg_update_bits(pmic->mfd, reg, BBCH_BBSEL_MASK,
						selector << BBCH_BBSEL_SHIFT);
	}

	return -EINVAL;
}