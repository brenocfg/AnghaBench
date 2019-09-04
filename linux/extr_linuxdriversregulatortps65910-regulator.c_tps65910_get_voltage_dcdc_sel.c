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
struct tps65910_reg {int /*<<< orphan*/  mfd; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TPS65910_REG_VDD1 130 
#define  TPS65910_REG_VDD2 129 
 int /*<<< orphan*/  TPS65910_VDD1 ; 
 int /*<<< orphan*/  TPS65910_VDD1_OP ; 
 int /*<<< orphan*/  TPS65910_VDD1_SR ; 
 int /*<<< orphan*/  TPS65910_VDD2 ; 
 int /*<<< orphan*/  TPS65910_VDD2_OP ; 
 int /*<<< orphan*/  TPS65910_VDD2_SR ; 
#define  TPS65911_REG_VDDCTRL 128 
 int /*<<< orphan*/  TPS65911_VDDCTRL_OP ; 
 int /*<<< orphan*/  TPS65911_VDDCTRL_SR ; 
 int VDD1_OP_CMD_MASK ; 
 int VDD1_OP_SEL_MASK ; 
 int VDD1_SR_SEL_MASK ; 
 int VDD1_VGAIN_SEL_MASK ; 
 int VDD1_VGAIN_SEL_SHIFT ; 
 int VDD2_OP_CMD_MASK ; 
 int VDD2_OP_SEL_MASK ; 
 int VDD2_SR_SEL_MASK ; 
 int VDD2_VGAIN_SEL_MASK ; 
 int VDD2_VGAIN_SEL_SHIFT ; 
 int VDDCTRL_OP_CMD_MASK ; 
 int VDDCTRL_OP_SEL_MASK ; 
 int VDDCTRL_SR_SEL_MASK ; 
 struct tps65910_reg* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int tps65910_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int tps65910_get_voltage_dcdc_sel(struct regulator_dev *dev)
{
	struct tps65910_reg *pmic = rdev_get_drvdata(dev);
	int ret, id = rdev_get_id(dev);
	int opvsel = 0, srvsel = 0, vselmax = 0, mult = 0, sr = 0;

	switch (id) {
	case TPS65910_REG_VDD1:
		ret = tps65910_reg_read(pmic->mfd, TPS65910_VDD1_OP, &opvsel);
		if (ret < 0)
			return ret;
		ret = tps65910_reg_read(pmic->mfd, TPS65910_VDD1, &mult);
		if (ret < 0)
			return ret;
		mult = (mult & VDD1_VGAIN_SEL_MASK) >> VDD1_VGAIN_SEL_SHIFT;
		ret = tps65910_reg_read(pmic->mfd, TPS65910_VDD1_SR, &srvsel);
		if (ret < 0)
			return ret;
		sr = opvsel & VDD1_OP_CMD_MASK;
		opvsel &= VDD1_OP_SEL_MASK;
		srvsel &= VDD1_SR_SEL_MASK;
		vselmax = 75;
		break;
	case TPS65910_REG_VDD2:
		ret = tps65910_reg_read(pmic->mfd, TPS65910_VDD2_OP, &opvsel);
		if (ret < 0)
			return ret;
		ret = tps65910_reg_read(pmic->mfd, TPS65910_VDD2, &mult);
		if (ret < 0)
			return ret;
		mult = (mult & VDD2_VGAIN_SEL_MASK) >> VDD2_VGAIN_SEL_SHIFT;
		ret = tps65910_reg_read(pmic->mfd, TPS65910_VDD2_SR, &srvsel);
		if (ret < 0)
			return ret;
		sr = opvsel & VDD2_OP_CMD_MASK;
		opvsel &= VDD2_OP_SEL_MASK;
		srvsel &= VDD2_SR_SEL_MASK;
		vselmax = 75;
		break;
	case TPS65911_REG_VDDCTRL:
		ret = tps65910_reg_read(pmic->mfd, TPS65911_VDDCTRL_OP,
					&opvsel);
		if (ret < 0)
			return ret;
		ret = tps65910_reg_read(pmic->mfd, TPS65911_VDDCTRL_SR,
					&srvsel);
		if (ret < 0)
			return ret;
		sr = opvsel & VDDCTRL_OP_CMD_MASK;
		opvsel &= VDDCTRL_OP_SEL_MASK;
		srvsel &= VDDCTRL_SR_SEL_MASK;
		vselmax = 64;
		break;
	}

	/* multiplier 0 == 1 but 2,3 normal */
	if (!mult)
		mult = 1;

	if (sr) {
		/* normalise to valid range */
		if (srvsel < 3)
			srvsel = 3;
		if (srvsel > vselmax)
			srvsel = vselmax;
		return srvsel - 3;
	} else {

		/* normalise to valid range*/
		if (opvsel < 3)
			opvsel = 3;
		if (opvsel > vselmax)
			opvsel = vselmax;
		return opvsel - 3;
	}
	return -EINVAL;
}