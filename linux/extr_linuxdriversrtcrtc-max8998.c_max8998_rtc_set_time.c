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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_time {int dummy; } ;
struct max8998_rtc_info {scalar_t__ lp3974_bug_workaround; int /*<<< orphan*/  rtc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8998_RTC_SEC ; 
 struct max8998_rtc_info* dev_get_drvdata (struct device*) ; 
 int max8998_bulk_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max8998_tm_to_data (struct rtc_time*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int max8998_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct max8998_rtc_info *info = dev_get_drvdata(dev);
	u8 data[8];
	int ret;

	max8998_tm_to_data(tm, data);

	ret = max8998_bulk_write(info->rtc, MAX8998_RTC_SEC, 8, data);

	if (info->lp3974_bug_workaround)
		msleep(2000);

	return ret;
}