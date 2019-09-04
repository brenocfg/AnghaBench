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
struct spear_rtc_config {scalar_t__ ioaddr; } ;
struct rtc_time {unsigned int tm_sec; unsigned int tm_min; unsigned int tm_hour; unsigned int tm_mday; unsigned int tm_mon; unsigned int tm_year; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ DATE_REG ; 
 unsigned int HOUR_SHIFT ; 
 unsigned int MDAY_SHIFT ; 
 unsigned int MINUTE_SHIFT ; 
 unsigned int MONTH_SHIFT ; 
 unsigned int SECOND_SHIFT ; 
 scalar_t__ TIME_REG ; 
 unsigned int YEAR_SHIFT ; 
 struct spear_rtc_config* dev_get_drvdata (struct device*) ; 
 int is_write_complete (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  rtc_wait_not_busy (struct spear_rtc_config*) ; 
 int /*<<< orphan*/  tm2bcd (struct rtc_time*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int spear_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct spear_rtc_config *config = dev_get_drvdata(dev);
	unsigned int time, date;

	tm2bcd(tm);

	rtc_wait_not_busy(config);
	time = (tm->tm_sec << SECOND_SHIFT) | (tm->tm_min << MINUTE_SHIFT) |
		(tm->tm_hour << HOUR_SHIFT);
	date = (tm->tm_mday << MDAY_SHIFT) | (tm->tm_mon << MONTH_SHIFT) |
		(tm->tm_year << YEAR_SHIFT);
	writel(time, config->ioaddr + TIME_REG);
	writel(date, config->ioaddr + DATE_REG);

	return is_write_complete(config);
}