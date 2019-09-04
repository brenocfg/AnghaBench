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
struct device {int dummy; } ;
struct cmos_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_AIE ; 
 int /*<<< orphan*/  cmos_irq_disable (struct cmos_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmos_irq_enable (struct cmos_rtc*,int /*<<< orphan*/ ) ; 
 struct cmos_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int cmos_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct cmos_rtc	*cmos = dev_get_drvdata(dev);
	unsigned long	flags;

	spin_lock_irqsave(&rtc_lock, flags);

	if (enabled)
		cmos_irq_enable(cmos, RTC_AIE);
	else
		cmos_irq_disable(cmos, RTC_AIE);

	spin_unlock_irqrestore(&rtc_lock, flags);
	return 0;
}