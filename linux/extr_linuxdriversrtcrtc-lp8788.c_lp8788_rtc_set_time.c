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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; } ;
struct lp8788_rtc {struct lp8788* lp; } ;
struct lp8788 {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int LP8788_BASE_YEAR ; 
 int LP8788_MONTH_OFFSET ; 
 scalar_t__ LP8788_RTC_SEC ; 
 size_t LPTIME_HOUR ; 
 int /*<<< orphan*/  LPTIME_MAX ; 
 size_t LPTIME_MDAY ; 
 size_t LPTIME_MIN ; 
 size_t LPTIME_MON ; 
 size_t LPTIME_SEC ; 
 size_t LPTIME_YEAR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct lp8788_rtc* dev_get_drvdata (struct device*) ; 
 int lp8788_write_byte (struct lp8788*,scalar_t__,int) ; 

__attribute__((used)) static int lp8788_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct lp8788_rtc *rtc = dev_get_drvdata(dev);
	struct lp8788 *lp = rtc->lp;
	u8 data[LPTIME_MAX - 1];
	int ret, i, year;

	year = tm->tm_year + 1900 - LP8788_BASE_YEAR;
	if (year < 0) {
		dev_err(lp->dev, "invalid year: %d\n", year);
		return -EINVAL;
	}

	/* because rtc weekday is a readonly register, do not update */
	data[LPTIME_SEC]  = tm->tm_sec;
	data[LPTIME_MIN]  = tm->tm_min;
	data[LPTIME_HOUR] = tm->tm_hour;
	data[LPTIME_MDAY] = tm->tm_mday;
	data[LPTIME_MON]  = tm->tm_mon + LP8788_MONTH_OFFSET;
	data[LPTIME_YEAR] = year;

	for (i = 0; i < ARRAY_SIZE(data); i++) {
		ret = lp8788_write_byte(lp, LP8788_RTC_SEC + i, data[i]);
		if (ret)
			return ret;
	}

	return 0;
}