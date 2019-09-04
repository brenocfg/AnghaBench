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
typedef  scalar_t__ u32 ;
struct rtc_wkalrm {int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;
struct cros_ec_rtc {struct cros_ec_device* cros_ec; } ;
struct cros_ec_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_RTC_GET_ALARM ; 
 int /*<<< orphan*/  EC_CMD_RTC_GET_VALUE ; 
 int cros_ec_rtc_get (struct cros_ec_device*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct cros_ec_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cros_ec_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(dev);
	struct cros_ec_device *cros_ec = cros_ec_rtc->cros_ec;
	int ret;
	u32 current_time, alarm_offset;

	/*
	 * The EC host command for getting the alarm is relative (i.e. 5
	 * seconds from now) whereas rtc_wkalrm is absolute. Get the current
	 * RTC time first so we can calculate the relative time.
	 */
	ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_VALUE, &current_time);
	if (ret < 0) {
		dev_err(dev, "error getting time: %d\n", ret);
		return ret;
	}

	ret = cros_ec_rtc_get(cros_ec, EC_CMD_RTC_GET_ALARM, &alarm_offset);
	if (ret < 0) {
		dev_err(dev, "error getting alarm: %d\n", ret);
		return ret;
	}

	rtc_time64_to_tm(current_time + alarm_offset, &alrm->time);

	return 0;
}