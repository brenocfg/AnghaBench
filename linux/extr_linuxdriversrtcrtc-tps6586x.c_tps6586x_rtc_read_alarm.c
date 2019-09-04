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
typedef  unsigned long time64_t ;
struct rtc_wkalrm {int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_ALARM1_HI ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned long,int /*<<< orphan*/ *) ; 
 struct device* to_tps6586x_dev (struct device*) ; 
 int tps6586x_reads (struct device*,int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static int tps6586x_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct device *tps_dev = to_tps6586x_dev(dev);
	unsigned long ticks;
	time64_t seconds;
	u8 buff[3];
	int ret;

	ret = tps6586x_reads(tps_dev, RTC_ALARM1_HI, sizeof(buff), buff);
	if (ret) {
		dev_err(dev, "read RTC_ALARM1_HI failed with err %d\n", ret);
		return ret;
	}

	ticks = (buff[0] << 16) | (buff[1] << 8) | buff[2];
	seconds = ticks >> 10;

	rtc_time64_to_tm(seconds, &alrm->time);
	return 0;
}