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
typedef  scalar_t__ u32 ;
struct sunxi_rtc_dev {TYPE_1__* data_year; scalar_t__ base; } ;
struct rtc_time {int tm_mon; int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUNXI_DATE_GET_DAY_VALUE (scalar_t__) ; 
 int SUNXI_DATE_GET_MON_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  SUNXI_DATE_GET_YEAR_VALUE (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ SUNXI_RTC_HMS ; 
 scalar_t__ SUNXI_RTC_YMD ; 
 int /*<<< orphan*/  SUNXI_TIME_GET_HOUR_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  SUNXI_TIME_GET_MIN_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  SUNXI_TIME_GET_SEC_VALUE (scalar_t__) ; 
 scalar_t__ SUNXI_YEAR_OFF (TYPE_1__*) ; 
 struct sunxi_rtc_dev* dev_get_drvdata (struct device*) ; 
 scalar_t__ readl (scalar_t__) ; 

__attribute__((used)) static int sunxi_rtc_gettime(struct device *dev, struct rtc_time *rtc_tm)
{
	struct sunxi_rtc_dev *chip = dev_get_drvdata(dev);
	u32 date, time;

	/*
	 * read again in case it changes
	 */
	do {
		date = readl(chip->base + SUNXI_RTC_YMD);
		time = readl(chip->base + SUNXI_RTC_HMS);
	} while ((date != readl(chip->base + SUNXI_RTC_YMD)) ||
		 (time != readl(chip->base + SUNXI_RTC_HMS)));

	rtc_tm->tm_sec  = SUNXI_TIME_GET_SEC_VALUE(time);
	rtc_tm->tm_min  = SUNXI_TIME_GET_MIN_VALUE(time);
	rtc_tm->tm_hour = SUNXI_TIME_GET_HOUR_VALUE(time);

	rtc_tm->tm_mday = SUNXI_DATE_GET_DAY_VALUE(date);
	rtc_tm->tm_mon  = SUNXI_DATE_GET_MON_VALUE(date);
	rtc_tm->tm_year = SUNXI_DATE_GET_YEAR_VALUE(date,
					chip->data_year->mask);

	rtc_tm->tm_mon  -= 1;

	/*
	 * switch from (data_year->min)-relative offset to
	 * a (1900)-relative one
	 */
	rtc_tm->tm_year += SUNXI_YEAR_OFF(chip->data_year);

	return 0;
}