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
typedef  scalar_t__ u32 ;
struct sprd_rtc {int valid; scalar_t__ base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 scalar_t__ SPRD_RTC_POWER_RESET_VALUE ; 
 scalar_t__ SPRD_RTC_PWR_STS ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int sprd_rtc_check_power_down(struct sprd_rtc *rtc)
{
	u32 val;
	int ret;

	ret = regmap_read(rtc->regmap, rtc->base + SPRD_RTC_PWR_STS, &val);
	if (ret)
		return ret;

	/*
	 * If the RTC power status value is SPRD_RTC_POWER_RESET_VALUE, which
	 * means the RTC has been powered down, so the RTC time values are
	 * invalid.
	 */
	rtc->valid = val == SPRD_RTC_POWER_RESET_VALUE ? false : true;
	return 0;
}