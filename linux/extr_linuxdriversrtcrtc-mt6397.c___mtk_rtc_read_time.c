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
typedef  void* u16 ;
struct rtc_time {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct mt6397_rtc {int /*<<< orphan*/  lock; scalar_t__ addr_base; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int RTC_OFFSET_COUNT ; 
 size_t RTC_OFFSET_DOM ; 
 size_t RTC_OFFSET_HOUR ; 
 size_t RTC_OFFSET_MIN ; 
 size_t RTC_OFFSET_MTH ; 
 size_t RTC_OFFSET_SEC ; 
 size_t RTC_OFFSET_YEAR ; 
 scalar_t__ RTC_TC_SEC ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,scalar_t__,void**,int) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 

__attribute__((used)) static int __mtk_rtc_read_time(struct mt6397_rtc *rtc,
			       struct rtc_time *tm, int *sec)
{
	int ret;
	u16 data[RTC_OFFSET_COUNT];

	mutex_lock(&rtc->lock);
	ret = regmap_bulk_read(rtc->regmap, rtc->addr_base + RTC_TC_SEC,
			       data, RTC_OFFSET_COUNT);
	if (ret < 0)
		goto exit;

	tm->tm_sec = data[RTC_OFFSET_SEC];
	tm->tm_min = data[RTC_OFFSET_MIN];
	tm->tm_hour = data[RTC_OFFSET_HOUR];
	tm->tm_mday = data[RTC_OFFSET_DOM];
	tm->tm_mon = data[RTC_OFFSET_MTH];
	tm->tm_year = data[RTC_OFFSET_YEAR];

	ret = regmap_read(rtc->regmap, rtc->addr_base + RTC_TC_SEC, sec);
exit:
	mutex_unlock(&rtc->lock);
	return ret;
}