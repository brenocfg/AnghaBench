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

/* Variables and functions */
 int /*<<< orphan*/  TWL_MODULE_PM_RECEIVER ; 
 int /*<<< orphan*/  VREG_GRP ; 
 int /*<<< orphan*/  rdev_get_drvdata (struct regulator_dev*) ; 
 int twlreg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twlreg_grp(struct regulator_dev *rdev)
{
	return twlreg_read(rdev_get_drvdata(rdev), TWL_MODULE_PM_RECEIVER,
								 VREG_GRP);
}