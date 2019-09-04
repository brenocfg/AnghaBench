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
typedef  int u32 ;
struct regulator_dev {int dummy; } ;
struct as3722_regulators {int /*<<< orphan*/  dev; struct as3722* as3722; } ;
struct as3722 {int dummy; } ;

/* Variables and functions */
 int AS3722_OVCURRENT_DEB_REG ; 
 int AS3722_OVCURRENT_REG ; 
 int AS3722_OVCURRENT_SD0_TRIP_MASK ; 
 int AS3722_OVCURRENT_SD1_TRIP_MASK ; 
 int AS3722_OVCURRENT_SD6_TRIP_MASK ; 
#define  AS3722_REGULATOR_ID_SD0 130 
#define  AS3722_REGULATOR_ID_SD1 129 
#define  AS3722_REGULATOR_ID_SD6 128 
 int EINVAL ; 
 int as3722_read (struct as3722*,int,int*) ; 
 int* as3722_sd016_current ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,int) ; 
 int ffs (int) ; 
 struct as3722_regulators* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int as3722_sd016_get_current_limit(struct regulator_dev *rdev)
{
	struct as3722_regulators *as3722_regs = rdev_get_drvdata(rdev);
	struct as3722 *as3722 = as3722_regs->as3722;
	int id = rdev_get_id(rdev);
	u32 val, reg;
	int mask;
	int ret;

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
	ret = as3722_read(as3722, reg, &val);
	if (ret < 0) {
		dev_err(as3722_regs->dev, "Reg 0x%02x read failed: %d\n",
			reg, ret);
		return ret;
	}
	val &= mask;
	val >>= ffs(mask) - 1;
	if (val == 3)
		return -EINVAL;
	return as3722_sd016_current[val];
}