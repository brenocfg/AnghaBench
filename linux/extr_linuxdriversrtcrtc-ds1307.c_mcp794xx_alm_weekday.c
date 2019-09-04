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
struct rtc_time {int tm_wday; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int div_s64 (int /*<<< orphan*/ ,int) ; 
 int ds1307_get_time (struct device*,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int mcp794xx_alm_weekday(struct device *dev, struct rtc_time *tm_alarm)
{
	struct rtc_time tm_now;
	int days_now, days_alarm, ret;

	ret = ds1307_get_time(dev, &tm_now);
	if (ret)
		return ret;

	days_now = div_s64(rtc_tm_to_time64(&tm_now), 24 * 60 * 60);
	days_alarm = div_s64(rtc_tm_to_time64(tm_alarm), 24 * 60 * 60);

	return (tm_now.tm_wday + days_alarm - days_now) % 7 + 1;
}