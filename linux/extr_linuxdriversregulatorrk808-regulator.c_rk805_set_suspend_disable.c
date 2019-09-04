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
struct regulator_dev {TYPE_1__* desc; int /*<<< orphan*/  regmap; } ;
struct TYPE_2__ {unsigned int enable_reg; int /*<<< orphan*/  enable_mask; } ;

/* Variables and functions */
 unsigned int RK808_SLP_SET_OFF_REG_OFFSET ; 
 int regmap_update_bits (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk805_set_suspend_disable(struct regulator_dev *rdev)
{
	unsigned int reg;

	reg = rdev->desc->enable_reg + RK808_SLP_SET_OFF_REG_OFFSET;

	return regmap_update_bits(rdev->regmap, reg,
				  rdev->desc->enable_mask,
				  0);
}