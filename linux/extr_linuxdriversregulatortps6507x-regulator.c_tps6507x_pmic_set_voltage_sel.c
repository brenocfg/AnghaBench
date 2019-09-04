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
struct tps6507x_pmic {TYPE_1__** info; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  defdcdc_default; } ;

/* Variables and functions */
 int EINVAL ; 
#define  TPS6507X_DCDC_1 132 
#define  TPS6507X_DCDC_2 131 
#define  TPS6507X_DCDC_3 130 
 int TPS6507X_DEFDCDCX_DCDC_MASK ; 
#define  TPS6507X_LDO_1 129 
#define  TPS6507X_LDO_2 128 
 int TPS6507X_REG_DEFDCDC1 ; 
 int TPS6507X_REG_DEFDCDC2_HIGH ; 
 int TPS6507X_REG_DEFDCDC2_LOW ; 
 int TPS6507X_REG_DEFDCDC3_HIGH ; 
 int TPS6507X_REG_DEFDCDC3_LOW ; 
 int TPS6507X_REG_DEFLDO2 ; 
 int TPS6507X_REG_DEFLDO2_LDO2_MASK ; 
 int TPS6507X_REG_LDO_CTRL1 ; 
 int TPS6507X_REG_LDO_CTRL1_LDO1_MASK ; 
 struct tps6507x_pmic* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 
 int tps6507x_pmic_reg_read (struct tps6507x_pmic*,int) ; 
 int tps6507x_pmic_reg_write (struct tps6507x_pmic*,int,int) ; 

__attribute__((used)) static int tps6507x_pmic_set_voltage_sel(struct regulator_dev *dev,
					  unsigned selector)
{
	struct tps6507x_pmic *tps = rdev_get_drvdata(dev);
	int data, rid = rdev_get_id(dev);
	u8 reg, mask;

	switch (rid) {
	case TPS6507X_DCDC_1:
		reg = TPS6507X_REG_DEFDCDC1;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		break;
	case TPS6507X_DCDC_2:
		if (tps->info[rid]->defdcdc_default)
			reg = TPS6507X_REG_DEFDCDC2_HIGH;
		else
			reg = TPS6507X_REG_DEFDCDC2_LOW;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		break;
	case TPS6507X_DCDC_3:
		if (tps->info[rid]->defdcdc_default)
			reg = TPS6507X_REG_DEFDCDC3_HIGH;
		else
			reg = TPS6507X_REG_DEFDCDC3_LOW;
		mask = TPS6507X_DEFDCDCX_DCDC_MASK;
		break;
	case TPS6507X_LDO_1:
		reg = TPS6507X_REG_LDO_CTRL1;
		mask = TPS6507X_REG_LDO_CTRL1_LDO1_MASK;
		break;
	case TPS6507X_LDO_2:
		reg = TPS6507X_REG_DEFLDO2;
		mask = TPS6507X_REG_DEFLDO2_LDO2_MASK;
		break;
	default:
		return -EINVAL;
	}

	data = tps6507x_pmic_reg_read(tps, reg);
	if (data < 0)
		return data;

	data &= ~mask;
	data |= selector;

	return tps6507x_pmic_reg_write(tps, reg, data);
}