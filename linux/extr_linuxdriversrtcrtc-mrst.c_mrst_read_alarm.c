#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; scalar_t__ pending; TYPE_1__ time; } ;
struct mrst_rtc {scalar_t__ irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 unsigned char RTC_AIE ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  RTC_HOURS_ALARM ; 
 int /*<<< orphan*/  RTC_MINUTES_ALARM ; 
 int /*<<< orphan*/  RTC_SECONDS_ALARM ; 
 struct mrst_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 void* vrtc_cmos_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mrst_read_alarm(struct device *dev, struct rtc_wkalrm *t)
{
	struct mrst_rtc	*mrst = dev_get_drvdata(dev);
	unsigned char rtc_control;

	if (mrst->irq <= 0)
		return -EIO;

	/* vRTC only supports binary mode */
	spin_lock_irq(&rtc_lock);
	t->time.tm_sec = vrtc_cmos_read(RTC_SECONDS_ALARM);
	t->time.tm_min = vrtc_cmos_read(RTC_MINUTES_ALARM);
	t->time.tm_hour = vrtc_cmos_read(RTC_HOURS_ALARM);

	rtc_control = vrtc_cmos_read(RTC_CONTROL);
	spin_unlock_irq(&rtc_lock);

	t->enabled = !!(rtc_control & RTC_AIE);
	t->pending = 0;

	return 0;
}