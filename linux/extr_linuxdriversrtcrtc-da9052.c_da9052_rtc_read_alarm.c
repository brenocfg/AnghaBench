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
struct rtc_time {int dummy; } ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; struct rtc_time time; } ;
struct device {int dummy; } ;
struct da9052_rtc {int dummy; } ;

/* Variables and functions */
 int da9052_read_alarm (struct da9052_rtc*,struct rtc_time*) ; 
 int /*<<< orphan*/  da9052_rtc_get_alarm_status (struct da9052_rtc*) ; 
 struct da9052_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_err (struct da9052_rtc*,char*,int) ; 

__attribute__((used)) static int da9052_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	int ret;
	struct rtc_time *tm = &alrm->time;
	struct da9052_rtc *rtc = dev_get_drvdata(dev);

	ret = da9052_read_alarm(rtc, tm);
	if (ret < 0) {
		rtc_err(rtc, "failed to read RTC alarm: %d\n", ret);
		return ret;
	}

	alrm->enabled = da9052_rtc_get_alarm_status(rtc);
	return 0;
}