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
struct ltv350qv {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int LTV_DRIVE_CURRENT (int) ; 
 int LTV_FWI (int) ; 
 int /*<<< orphan*/  LTV_GATECTL2 ; 
 int LTV_NW_INV_1LINE ; 
 int /*<<< orphan*/  LTV_PWRCTL1 ; 
 int /*<<< orphan*/  LTV_PWRCTL2 ; 
 int LTV_SUPPLY_CURRENT (int) ; 
 int LTV_VCOM_DISABLE ; 
 int ltv350qv_write_reg (struct ltv350qv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int ltv350qv_power_off(struct ltv350qv *lcd)
{
	int ret;

	/* Display Off Sequence */
	ret = ltv350qv_write_reg(lcd, LTV_PWRCTL1,
				 LTV_VCOM_DISABLE
				 | LTV_DRIVE_CURRENT(5)
				 | LTV_SUPPLY_CURRENT(5));
	ret |= ltv350qv_write_reg(lcd, LTV_GATECTL2,
				  LTV_NW_INV_1LINE | LTV_FWI(3));

	/* Power down setting 1 */
	ret |= ltv350qv_write_reg(lcd, LTV_PWRCTL2, 0x0000);

	/* Wait at least 1 ms */
	usleep_range(1000, 1100);

	/* Power down setting 2 */
	ret |= ltv350qv_write_reg(lcd, LTV_PWRCTL1, LTV_VCOM_DISABLE);

	/*
	 * No point in trying to recover here. If we can't switch the
	 * panel off, what are we supposed to do other than inform the
	 * user about the failure?
	 */
	if (ret)
		return -EIO;

	/* Display power should now be OFF */
	return 0;
}