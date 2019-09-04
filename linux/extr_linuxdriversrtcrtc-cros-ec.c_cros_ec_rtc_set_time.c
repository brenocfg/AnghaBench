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
typedef  int /*<<< orphan*/  u32 ;
typedef  scalar_t__ time64_t ;
struct rtc_time {int dummy; } ;
struct device {int dummy; } ;
struct cros_ec_rtc {struct cros_ec_device* cros_ec; } ;
struct cros_ec_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EC_CMD_RTC_SET_VALUE ; 
 int EINVAL ; 
 scalar_t__ U32_MAX ; 
 int cros_ec_rtc_set (struct cros_ec_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct cros_ec_rtc* dev_get_drvdata (struct device*) ; 
 scalar_t__ rtc_tm_to_time64 (struct rtc_time*) ; 

__attribute__((used)) static int cros_ec_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct cros_ec_rtc *cros_ec_rtc = dev_get_drvdata(dev);
	struct cros_ec_device *cros_ec = cros_ec_rtc->cros_ec;
	int ret;
	time64_t time;

	time = rtc_tm_to_time64(tm);
	if (time < 0 || time > U32_MAX)
		return -EINVAL;

	ret = cros_ec_rtc_set(cros_ec, EC_CMD_RTC_SET_VALUE, (u32)time);
	if (ret < 0) {
		dev_err(dev, "error setting time: %d\n", ret);
		return ret;
	}

	return 0;
}