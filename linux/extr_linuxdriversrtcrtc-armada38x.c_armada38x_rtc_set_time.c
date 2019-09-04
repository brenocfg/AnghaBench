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
struct device {int dummy; } ;
struct armada38x_rtc {int /*<<< orphan*/  lock; int /*<<< orphan*/  initialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_TIME ; 
 int /*<<< orphan*/  armada38x_rtc_reset (struct armada38x_rtc*) ; 
 struct armada38x_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_delayed_write (unsigned long,struct armada38x_rtc*,int /*<<< orphan*/ ) ; 
 int rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int armada38x_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct armada38x_rtc *rtc = dev_get_drvdata(dev);
	int ret = 0;
	unsigned long time, flags;

	ret = rtc_tm_to_time(tm, &time);

	if (ret)
		goto out;

	if (!rtc->initialized)
		armada38x_rtc_reset(rtc);

	spin_lock_irqsave(&rtc->lock, flags);
	rtc_delayed_write(time, rtc, RTC_TIME);
	spin_unlock_irqrestore(&rtc->lock, flags);

out:
	return ret;
}