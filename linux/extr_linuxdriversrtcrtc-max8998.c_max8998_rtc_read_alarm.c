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
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct max8998_rtc_info {int /*<<< orphan*/  rtc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ALARM0_STATUS ; 
 int /*<<< orphan*/  MAX8998_ALARM0_CONF ; 
 int /*<<< orphan*/  MAX8998_ALARM0_SEC ; 
 int /*<<< orphan*/  MAX8998_RTC_STATUS ; 
 struct max8998_rtc_info* dev_get_drvdata (struct device*) ; 
 int max8998_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  max8998_data_to_tm (int*,int /*<<< orphan*/ *) ; 
 int max8998_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int max8998_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct max8998_rtc_info *info = dev_get_drvdata(dev);
	u8 data[8];
	u8 val;
	int ret;

	ret = max8998_bulk_read(info->rtc, MAX8998_ALARM0_SEC, 8, data);
	if (ret < 0)
		return ret;

	max8998_data_to_tm(data, &alrm->time);

	ret = max8998_read_reg(info->rtc, MAX8998_ALARM0_CONF, &val);
	if (ret < 0)
		return ret;

	alrm->enabled = !!val;

	ret = max8998_read_reg(info->rtc, MAX8998_RTC_STATUS, &val);
	if (ret < 0)
		return ret;

	if (val & ALARM0_STATUS)
		alrm->pending = 1;
	else
		alrm->pending = 0;

	return 0;
}