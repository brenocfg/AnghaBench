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
typedef  int u32 ;
struct sun6i_rtc_dev {scalar_t__ base; } ;
struct rtc_time {int tm_year; int tm_mon; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; int /*<<< orphan*/  tm_mday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ETIMEDOUT ; 
 int SUN6I_DATE_SET_DAY_VALUE (int /*<<< orphan*/ ) ; 
 int SUN6I_DATE_SET_MON_VALUE (int) ; 
 int SUN6I_DATE_SET_YEAR_VALUE (int) ; 
 int SUN6I_LEAP_SET_VALUE (int) ; 
 int /*<<< orphan*/  SUN6I_LOSC_CTRL ; 
 int /*<<< orphan*/  SUN6I_LOSC_CTRL_ACC_MASK ; 
 int /*<<< orphan*/  SUN6I_LOSC_CTRL_RTC_HMS_ACC ; 
 int /*<<< orphan*/  SUN6I_LOSC_CTRL_RTC_YMD_ACC ; 
 scalar_t__ SUN6I_RTC_HMS ; 
 scalar_t__ SUN6I_RTC_YMD ; 
 int SUN6I_TIME_SET_HOUR_VALUE (int /*<<< orphan*/ ) ; 
 int SUN6I_TIME_SET_MIN_VALUE (int /*<<< orphan*/ ) ; 
 int SUN6I_TIME_SET_SEC_VALUE (int /*<<< orphan*/ ) ; 
 int SUN6I_YEAR_MAX ; 
 int SUN6I_YEAR_MIN ; 
 scalar_t__ SUN6I_YEAR_OFF ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 struct sun6i_rtc_dev* dev_get_drvdata (struct device*) ; 
 scalar_t__ is_leap_year (int) ; 
 scalar_t__ sun6i_rtc_wait (struct sun6i_rtc_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sun6i_rtc_settime(struct device *dev, struct rtc_time *rtc_tm)
{
	struct sun6i_rtc_dev *chip = dev_get_drvdata(dev);
	u32 date = 0;
	u32 time = 0;
	int year;

	year = rtc_tm->tm_year + 1900;
	if (year < SUN6I_YEAR_MIN || year > SUN6I_YEAR_MAX) {
		dev_err(dev, "rtc only supports year in range %d - %d\n",
			SUN6I_YEAR_MIN, SUN6I_YEAR_MAX);
		return -EINVAL;
	}

	rtc_tm->tm_year -= SUN6I_YEAR_OFF;
	rtc_tm->tm_mon += 1;

	date = SUN6I_DATE_SET_DAY_VALUE(rtc_tm->tm_mday) |
		SUN6I_DATE_SET_MON_VALUE(rtc_tm->tm_mon)  |
		SUN6I_DATE_SET_YEAR_VALUE(rtc_tm->tm_year);

	if (is_leap_year(year))
		date |= SUN6I_LEAP_SET_VALUE(1);

	time = SUN6I_TIME_SET_SEC_VALUE(rtc_tm->tm_sec)  |
		SUN6I_TIME_SET_MIN_VALUE(rtc_tm->tm_min)  |
		SUN6I_TIME_SET_HOUR_VALUE(rtc_tm->tm_hour);

	/* Check whether registers are writable */
	if (sun6i_rtc_wait(chip, SUN6I_LOSC_CTRL,
			   SUN6I_LOSC_CTRL_ACC_MASK, 50)) {
		dev_err(dev, "rtc is still busy.\n");
		return -EBUSY;
	}

	writel(time, chip->base + SUN6I_RTC_HMS);

	/*
	 * After writing the RTC HH-MM-SS register, the
	 * SUN6I_LOSC_CTRL_RTC_HMS_ACC bit is set and it will not
	 * be cleared until the real writing operation is finished
	 */

	if (sun6i_rtc_wait(chip, SUN6I_LOSC_CTRL,
			   SUN6I_LOSC_CTRL_RTC_HMS_ACC, 50)) {
		dev_err(dev, "Failed to set rtc time.\n");
		return -ETIMEDOUT;
	}

	writel(date, chip->base + SUN6I_RTC_YMD);

	/*
	 * After writing the RTC YY-MM-DD register, the
	 * SUN6I_LOSC_CTRL_RTC_YMD_ACC bit is set and it will not
	 * be cleared until the real writing operation is finished
	 */

	if (sun6i_rtc_wait(chip, SUN6I_LOSC_CTRL,
			   SUN6I_LOSC_CTRL_RTC_YMD_ACC, 50)) {
		dev_err(dev, "Failed to set rtc time.\n");
		return -ETIMEDOUT;
	}

	return 0;
}