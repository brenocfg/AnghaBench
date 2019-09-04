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
struct TYPE_2__ {unsigned int active_discharge_on; unsigned int active_discharge_off; int /*<<< orphan*/  active_discharge_mask; int /*<<< orphan*/  active_discharge_reg; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

int regulator_set_active_discharge_regmap(struct regulator_dev *rdev,
					  bool enable)
{
	unsigned int val;

	if (enable)
		val = rdev->desc->active_discharge_on;
	else
		val = rdev->desc->active_discharge_off;

	return regmap_update_bits(rdev->regmap,
				  rdev->desc->active_discharge_reg,
				  rdev->desc->active_discharge_mask, val);
}