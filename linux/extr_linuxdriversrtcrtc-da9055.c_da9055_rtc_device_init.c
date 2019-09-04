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
struct da9055_pdata {scalar_t__ reset_enable; } ;
struct da9055 {int dummy; } ;

/* Variables and functions */
 int DA9055_CRYSTAL_EN ; 
 int /*<<< orphan*/  DA9055_REG_ALARM_MO ; 
 int /*<<< orphan*/  DA9055_REG_CONTROL_B ; 
 int /*<<< orphan*/  DA9055_REG_EN_32K ; 
 int DA9055_RTC_EN ; 
 int DA9055_RTC_MODE_PD ; 
 int DA9055_RTC_MODE_SD ; 
 int DA9055_RTC_MODE_SD_SHIFT ; 
 int DA9055_RTC_TICK_WAKE_MASK ; 
 int da9055_reg_update (struct da9055*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int da9055_rtc_device_init(struct da9055 *da9055,
					struct da9055_pdata *pdata)
{
	int ret;

	/* Enable RTC and the internal Crystal */
	ret = da9055_reg_update(da9055, DA9055_REG_CONTROL_B,
				DA9055_RTC_EN, DA9055_RTC_EN);
	if (ret < 0)
		return ret;
	ret = da9055_reg_update(da9055, DA9055_REG_EN_32K,
				DA9055_CRYSTAL_EN, DA9055_CRYSTAL_EN);
	if (ret < 0)
		return ret;

	/* Enable RTC in Power Down mode */
	ret = da9055_reg_update(da9055, DA9055_REG_CONTROL_B,
				DA9055_RTC_MODE_PD, DA9055_RTC_MODE_PD);
	if (ret < 0)
		return ret;

	/* Enable RTC in Reset mode */
	if (pdata && pdata->reset_enable) {
		ret = da9055_reg_update(da9055, DA9055_REG_CONTROL_B,
					DA9055_RTC_MODE_SD,
					DA9055_RTC_MODE_SD <<
					DA9055_RTC_MODE_SD_SHIFT);
		if (ret < 0)
			return ret;
	}

	/* Disable the RTC TICK ALM */
	ret = da9055_reg_update(da9055, DA9055_REG_ALARM_MO,
				DA9055_RTC_TICK_WAKE_MASK, 0);
	if (ret < 0)
		return ret;

	return 0;
}