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
struct da9055_rtc {int alarm_enable; TYPE_1__* da9055; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_REG_ALARM_Y ; 
 int /*<<< orphan*/  DA9055_RTC_ALM_EN ; 
 int da9055_reg_update (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int da9055_rtc_enable_alarm(struct da9055_rtc *rtc, bool enable)
{
	int ret;
	if (enable) {
		ret = da9055_reg_update(rtc->da9055, DA9055_REG_ALARM_Y,
					DA9055_RTC_ALM_EN,
					DA9055_RTC_ALM_EN);
		if (ret != 0)
			dev_err(rtc->da9055->dev, "Failed to enable ALM: %d\n",
				ret);
		rtc->alarm_enable = 1;
	} else {
		ret = da9055_reg_update(rtc->da9055, DA9055_REG_ALARM_Y,
					DA9055_RTC_ALM_EN, 0);
		if (ret != 0)
			dev_err(rtc->da9055->dev,
				"Failed to disable ALM: %d\n", ret);
		rtc->alarm_enable = 0;
	}
	return ret;
}