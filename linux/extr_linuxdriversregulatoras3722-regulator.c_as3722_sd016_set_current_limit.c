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
typedef  int /*<<< orphan*/  u32 ;
struct regulator_dev {int dummy; } ;
struct as3722_regulators {int /*<<< orphan*/  dev; struct as3722* as3722; } ;
struct as3722 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AS3722_OVCURRENT_DEB_REG ; 
 int /*<<< orphan*/  AS3722_OVCURRENT_REG ; 
 int AS3722_OVCURRENT_SD0_TRIP_MASK ; 
 int AS3722_OVCURRENT_SD1_TRIP_MASK ; 
 int AS3722_OVCURRENT_SD6_TRIP_MASK ; 
#define  AS3722_REGULATOR_ID_SD0 130 
#define  AS3722_REGULATOR_ID_SD1 129 
#define  AS3722_REGULATOR_ID_SD6 128 
 int EINVAL ; 
 int as3722_current_to_index (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as3722_sd016_current ; 
 int as3722_update_bits (struct as3722*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int ffs (int) ; 
 struct as3722_regulators* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int as3722_sd016_set_current_limit(struct regulator_dev *rdev,
		int min_uA, int max_uA)
{
	struct as3722_regulators *as3722_regs = rdev_get_drvdata(rdev);
	struct as3722 *as3722 = as3722_regs->as3722;
	int id = rdev_get_id(rdev);
	int ret;
	int val;
	int mask;
	u32 reg;

	ret = as3722_current_to_index(min_uA, max_uA, as3722_sd016_current,
				ARRAY_SIZE(as3722_sd016_current));
	if (ret < 0) {
		dev_err(as3722_regs->dev,
			"Current range min:max = %d:%d does not support\n",
			min_uA, max_uA);
		return ret;
	}

	switch (id) {
	case AS3722_REGULATOR_ID_SD0:
		reg = AS3722_OVCURRENT_REG;
		mask = AS3722_OVCURRENT_SD0_TRIP_MASK;
		break;
	case AS3722_REGULATOR_ID_SD1:
		reg = AS3722_OVCURRENT_REG;
		mask = AS3722_OVCURRENT_SD1_TRIP_MASK;
		break;
	case AS3722_REGULATOR_ID_SD6:
		reg = AS3722_OVCURRENT_DEB_REG;
		mask = AS3722_OVCURRENT_SD6_TRIP_MASK;
		break;
	default:
		return -EINVAL;
	}
	ret <<= ffs(mask) - 1;
	val = ret & mask;
	return as3722_update_bits(as3722, reg, mask, val);
}