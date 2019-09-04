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
typedef  int u8 ;
struct spmi_regulator {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPMI_COMMON_REG_VOLTAGE_SET ; 
 int ULT_SMPS_RANGE_SPLIT ; 
 struct spmi_regulator* rdev_get_drvdata (struct regulator_dev*) ; 
 int spmi_sw_selector_to_hw (struct spmi_regulator*,unsigned int,int*,int*) ; 
 int spmi_vreg_update_bits (struct spmi_regulator*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int spmi_regulator_ult_lo_smps_set_voltage(struct regulator_dev *rdev,
						  unsigned selector)
{
	struct spmi_regulator *vreg = rdev_get_drvdata(rdev);
	int ret;
	u8 range_sel, voltage_sel;

	ret = spmi_sw_selector_to_hw(vreg, selector, &range_sel, &voltage_sel);
	if (ret)
		return ret;

	/*
	 * Calculate VSET based on range
	 * In case of range 0: voltage_sel is a 7 bit value, can be written
	 *			witout any modification.
	 * In case of range 1: voltage_sel is a 5 bit value, bits[7-5] set to
	 *			[011].
	 */
	if (range_sel == 1)
		voltage_sel |= ULT_SMPS_RANGE_SPLIT;

	return spmi_vreg_update_bits(vreg, SPMI_COMMON_REG_VOLTAGE_SET,
				     voltage_sel, 0xff);
}