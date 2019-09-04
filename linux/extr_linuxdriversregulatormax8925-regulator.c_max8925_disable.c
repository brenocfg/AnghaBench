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
struct max8925_regulator_info {int /*<<< orphan*/  enable_reg; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int LDO_I2C_EN_MASK ; 
 int LDO_I2C_EN_SHIFT ; 
 int LDO_SEQ_I2C ; 
 int LDO_SEQ_MASK ; 
 int LDO_SEQ_SHIFT ; 
 int max8925_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct max8925_regulator_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int max8925_disable(struct regulator_dev *rdev)
{
	struct max8925_regulator_info *info = rdev_get_drvdata(rdev);

	return max8925_set_bits(info->i2c, info->enable_reg,
				LDO_SEQ_MASK << LDO_SEQ_SHIFT |
				LDO_I2C_EN_MASK << LDO_I2C_EN_SHIFT,
				LDO_SEQ_I2C << LDO_SEQ_SHIFT);
}