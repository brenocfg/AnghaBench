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
struct twlreg_info {int features; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int TWL6030_CFG_STATE_GRP_SHIFT ; 
 int TWL6030_CFG_STATE_ON ; 
 int TWL6032_SUBCLASS ; 
 int /*<<< orphan*/  TWL_MODULE_PM_RECEIVER ; 
 int /*<<< orphan*/  VREG_STATE ; 
 struct twlreg_info* rdev_get_drvdata (struct regulator_dev*) ; 
 scalar_t__ twl_class_is_6030 () ; 
 int twlreg_grp (struct regulator_dev*) ; 
 int twlreg_write (struct twlreg_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int twl6030reg_enable(struct regulator_dev *rdev)
{
	struct twlreg_info	*info = rdev_get_drvdata(rdev);
	int			grp = 0;
	int			ret;

	if (!(twl_class_is_6030() && (info->features & TWL6032_SUBCLASS)))
		grp = twlreg_grp(rdev);
	if (grp < 0)
		return grp;

	ret = twlreg_write(info, TWL_MODULE_PM_RECEIVER, VREG_STATE,
			grp << TWL6030_CFG_STATE_GRP_SHIFT |
			TWL6030_CFG_STATE_ON);
	return ret;
}