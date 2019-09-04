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
struct max8998_rtc_info {int /*<<< orphan*/  rtc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX8998_RTC_SEC ; 
 struct max8998_rtc_info* dev_get_drvdata (struct device*) ; 
 int max8998_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  max8998_data_to_tm (int /*<<< orphan*/ *,struct rtc_time*) ; 

__attribute__((used)) static int max8998_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct max8998_rtc_info *info = dev_get_drvdata(dev);
	u8 data[8];
	int ret;

	ret = max8998_bulk_read(info->rtc, MAX8998_RTC_SEC, 8, data);
	if (ret < 0)
		return ret;

	max8998_data_to_tm(data, tm);

	return 0;
}