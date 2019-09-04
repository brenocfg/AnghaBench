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
typedef  int /*<<< orphan*/  u32 ;
struct regulator_dev {int dummy; } ;
struct as3722_regulators {int /*<<< orphan*/  dev; struct as3722* as3722; } ;
struct as3722 {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  vsel_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AS3722_LDO_ILIMIT_BIT ; 
 int /*<<< orphan*/  AS3722_LDO_ILIMIT_MASK ; 
 int as3722_current_to_index (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as3722_ldo_current ; 
 TYPE_1__* as3722_reg_lookup ; 
 int as3722_update_bits (struct as3722*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 struct as3722_regulators* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int as3722_ldo_set_current_limit(struct regulator_dev *rdev,
		int min_uA, int max_uA)
{
	struct as3722_regulators *as3722_regs = rdev_get_drvdata(rdev);
	struct as3722 *as3722 = as3722_regs->as3722;
	int id = rdev_get_id(rdev);
	int ret;
	u32 reg = 0;

	ret = as3722_current_to_index(min_uA, max_uA, as3722_ldo_current,
				ARRAY_SIZE(as3722_ldo_current));
	if (ret < 0) {
		dev_err(as3722_regs->dev,
			"Current range min:max = %d:%d does not support\n",
			min_uA, max_uA);
		return ret;
	}
	if (ret)
		reg = AS3722_LDO_ILIMIT_BIT;
	return as3722_update_bits(as3722, as3722_reg_lookup[id].vsel_reg,
			AS3722_LDO_ILIMIT_MASK, reg);
}