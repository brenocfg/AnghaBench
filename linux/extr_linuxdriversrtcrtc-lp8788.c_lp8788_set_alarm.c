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
struct rtc_time {int tm_year; int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int /*<<< orphan*/  tm_wday; } ;
struct rtc_wkalrm {int enabled; struct rtc_time time; } ;
struct lp8788_rtc {size_t alarm; struct lp8788* lp; } ;
struct lp8788 {int /*<<< orphan*/  dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  LP8788_ALM_EN_M ; 
 int LP8788_ALM_EN_S ; 
 int LP8788_BASE_YEAR ; 
 int LP8788_MONTH_OFFSET ; 
 size_t LPTIME_HOUR ; 
 int LPTIME_MAX ; 
 size_t LPTIME_MDAY ; 
 size_t LPTIME_MIN ; 
 size_t LPTIME_MON ; 
 size_t LPTIME_SEC ; 
 size_t LPTIME_WDAY ; 
 size_t LPTIME_YEAR ; 
 int _to_lp8788_wday (int /*<<< orphan*/ ) ; 
 int* addr_alarm_en ; 
 int* addr_alarm_sec ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct lp8788_rtc* dev_get_drvdata (struct device*) ; 
 int lp8788_update_bits (struct lp8788*,int,int /*<<< orphan*/ ,int) ; 
 int lp8788_write_byte (struct lp8788*,int,int) ; 

__attribute__((used)) static int lp8788_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct lp8788_rtc *rtc = dev_get_drvdata(dev);
	struct lp8788 *lp = rtc->lp;
	struct rtc_time *tm = &alarm->time;
	u8 addr, data[LPTIME_MAX];
	int ret, i, year;

	year = tm->tm_year + 1900 - LP8788_BASE_YEAR;
	if (year < 0) {
		dev_err(lp->dev, "invalid year: %d\n", year);
		return -EINVAL;
	}

	data[LPTIME_SEC]  = tm->tm_sec;
	data[LPTIME_MIN]  = tm->tm_min;
	data[LPTIME_HOUR] = tm->tm_hour;
	data[LPTIME_MDAY] = tm->tm_mday;
	data[LPTIME_MON]  = tm->tm_mon + LP8788_MONTH_OFFSET;
	data[LPTIME_YEAR] = year;
	data[LPTIME_WDAY] = _to_lp8788_wday(tm->tm_wday);

	for (i = 0; i < ARRAY_SIZE(data); i++) {
		addr = addr_alarm_sec[rtc->alarm] + i;
		ret = lp8788_write_byte(lp, addr, data[i]);
		if (ret)
			return ret;
	}

	alarm->enabled = 1;
	addr = addr_alarm_en[rtc->alarm];

	return lp8788_update_bits(lp, addr, LP8788_ALM_EN_M,
				alarm->enabled << LP8788_ALM_EN_S);
}