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
typedef  int /*<<< orphan*/  u8 ;
struct spmi_regulator {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_COMMON_MODE_BYPASS_MASK ; 
 int /*<<< orphan*/  SPMI_COMMON_REG_MODE ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int spmi_vreg_update_bits (struct spmi_regulator*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
spmi_regulator_common_set_bypass(struct regulator_dev *rdev, bool enable)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	u8 mask = SPMI_COMMON_MODE_BYPASS_MASK;
	u8 val = 0;

	if (enable)
		val = mask;

	return spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_MODE, val, mask);
}