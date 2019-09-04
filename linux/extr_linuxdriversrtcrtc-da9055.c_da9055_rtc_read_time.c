#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct device {int dummy; } ;
struct da9055_rtc {TYPE_1__* da9055; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9055_REG_COUNT_S ; 
 int DA9055_RTC_DAY ; 
 int DA9055_RTC_HOUR ; 
 int DA9055_RTC_MIN ; 
 int DA9055_RTC_MONTH ; 
 int DA9055_RTC_READ ; 
 int DA9055_RTC_SEC ; 
 int DA9055_RTC_YEAR ; 
 int EBUSY ; 
 int da9055_group_read (TYPE_1__*,int /*<<< orphan*/ ,int,int*) ; 
 int da9055_reg_read (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct da9055_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int da9055_rtc_read_time(struct device *dev, struct rtc_time *rtc_tm)
{
	struct da9055_rtc *rtc = dev_get_drvdata(dev);
	uint8_t v[6];
	int ret;

	ret = da9055_reg_read(rtc->da9055, DA9055_REG_COUNT_S);
	if (ret < 0)
		return ret;

	/*
	 * Registers are only valid when RTC_READ
	 * status bit is asserted
	 */
	if (!(ret & DA9055_RTC_READ))
		return -EBUSY;

	ret = da9055_group_read(rtc->da9055, DA9055_REG_COUNT_S, 6, v);
	if (ret < 0) {
		dev_err(rtc->da9055->dev, "Failed to read RTC time : %d\n",
			ret);
		return ret;
	}

	rtc_tm->tm_year = (v[5] & DA9055_RTC_YEAR) + 100;
	rtc_tm->tm_mon  = (v[4] & DA9055_RTC_MONTH) - 1;
	rtc_tm->tm_mday = v[3] & DA9055_RTC_DAY;
	rtc_tm->tm_hour = v[2] & DA9055_RTC_HOUR;
	rtc_tm->tm_min  = v[1] & DA9055_RTC_MIN;
	rtc_tm->tm_sec  = v[0] & DA9055_RTC_SEC;

	return 0;
}