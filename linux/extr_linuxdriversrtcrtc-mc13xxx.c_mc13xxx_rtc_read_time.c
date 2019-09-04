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
typedef  unsigned int time64_t ;
struct rtc_time {int dummy; } ;
struct mc13xxx_rtc {int /*<<< orphan*/  mc13xxx; int /*<<< orphan*/  valid; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  MC13XXX_RTCDAY ; 
 int /*<<< orphan*/  MC13XXX_RTCTOD ; 
 unsigned int SEC_PER_DAY ; 
 struct mc13xxx_rtc* dev_get_drvdata (struct device*) ; 
 int mc13xxx_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  rtc_time64_to_tm (unsigned int,struct rtc_time*) ; 

__attribute__((used)) static int mc13xxx_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct mc13xxx_rtc *priv = dev_get_drvdata(dev);
	unsigned int seconds, days1, days2;

	if (!priv->valid)
		return -ENODATA;

	do {
		int ret;

		ret = mc13xxx_reg_read(priv->mc13xxx, MC13XXX_RTCDAY, &days1);
		if (ret)
			return ret;

		ret = mc13xxx_reg_read(priv->mc13xxx, MC13XXX_RTCTOD, &seconds);
		if (ret)
			return ret;

		ret = mc13xxx_reg_read(priv->mc13xxx, MC13XXX_RTCDAY, &days2);
		if (ret)
			return ret;
	} while (days1 != days2);

	rtc_time64_to_tm((time64_t)days1 * SEC_PER_DAY + seconds, tm);

	return 0;
}