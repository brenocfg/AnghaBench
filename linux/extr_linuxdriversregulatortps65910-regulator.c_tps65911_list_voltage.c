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
struct tps65910_reg {TYPE_1__** info; } ;
struct regulator_dev {int dummy; } ;
struct TYPE_2__ {int* voltage_table; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int LDO_MIN_VOLT ; 
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

__attribute__((used)) static int tps65911_list_voltage(struct regulator_dev *dev, unsigned selector)
{
	struct tps65910_reg *pmic = rdev_get_drvdata(dev);
	int step_mv = 0, id = rdev_get_id(dev);

	switch (id) {
	case TPS65911_REG_LDO1:
	case TPS65911_REG_LDO2:
	case TPS65911_REG_LDO4:
		/* The first 5 values of the selector correspond to 1V */
		if (selector < 5)
			selector = 0;
		else
			selector -= 4;

		step_mv = 50;
		break;
	case TPS65911_REG_LDO3:
	case TPS65911_REG_LDO5:
	case TPS65911_REG_LDO6:
	case TPS65911_REG_LDO7:
	case TPS65911_REG_LDO8:
		/* The first 3 values of the selector correspond to 1V */
		if (selector < 3)
			selector = 0;
		else
			selector -= 2;

		step_mv = 100;
		break;
	case TPS65910_REG_VIO:
		return pmic->info[id]->voltage_table[selector];
	default:
		return -EINVAL;
	}

	return (LDO_MIN_VOLT + selector * step_mv) * 1000;
}