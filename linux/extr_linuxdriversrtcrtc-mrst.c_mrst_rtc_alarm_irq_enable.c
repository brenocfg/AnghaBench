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
struct mrst_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_AIE ; 
 struct mrst_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mrst_irq_disable (struct mrst_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrst_irq_enable (struct mrst_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int mrst_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct mrst_rtc	*mrst = dev_get_drvdata(dev);
	unsigned long	flags;

	spin_lock_irqsave(&rtc_lock, flags);
	if (enabled)
		mrst_irq_enable(mrst, RTC_AIE);
	else
		mrst_irq_disable(mrst, RTC_AIE);
	spin_unlock_irqrestore(&rtc_lock, flags);
	return 0;
}