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
struct twlreg_info {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TWL_MODULE_PM_RECEIVER ; 
 int /*<<< orphan*/  VREG_VOLTAGE_SMPS ; 
 struct twlreg_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int twlreg_read (struct twlreg_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl6030smps_get_voltage_sel(struct regulator_dev *rdev)
{
	struct twlreg_info	*info = rdev_get_drvdata(rdev);

	return twlreg_read(info, TWL_MODULE_PM_RECEIVER, VREG_VOLTAGE_SMPS);
}