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
struct da9055_rtc {int /*<<< orphan*/  da9055; } ;

/* Variables and functions */
 int da9055_read_alarm (int /*<<< orphan*/ ,struct rtc_time*) ; 
 int /*<<< orphan*/  da9055_rtc_get_alarm_status (int /*<<< orphan*/ ) ; 
 struct da9055_rtc* dev_get_drvdata (struct device*) ; 

__attribute__((used)) static int da9055_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	int ret;
	struct rtc_time *tm = &alrm->time;
	struct da9055_rtc *rtc = dev_get_drvdata(dev);

	ret = da9055_read_alarm(rtc->da9055, tm);

	if (ret)
		return ret;

	alrm->enabled = da9055_rtc_get_alarm_status(rtc->da9055);

	return 0;
}