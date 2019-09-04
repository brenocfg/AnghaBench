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
struct sa1100_rtc {int /*<<< orphan*/  lock; int /*<<< orphan*/  rtsr; struct rtc_device* rtc; } ;
struct rtc_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_UF ; 
 unsigned int RTSR_AL ; 
 unsigned int RTSR_ALE ; 
 unsigned int RTSR_HZ ; 
 unsigned int RTSR_HZE ; 
 struct sa1100_rtc* dev_get_drvdata (void*) ; 
 unsigned int readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,unsigned long) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sa1100_rtc_interrupt(int irq, void *dev_id)
{
	struct sa1100_rtc *info = dev_get_drvdata(dev_id);
	struct rtc_device *rtc = info->rtc;
	unsigned int rtsr;
	unsigned long events = 0;

	spin_lock(&info->lock);

	rtsr = readl_relaxed(info->rtsr);
	/* clear interrupt sources */
	writel_relaxed(0, info->rtsr);
	/* Fix for a nasty initialization problem the in SA11xx RTSR register.
	 * See also the comments in sa1100_rtc_probe(). */
	if (rtsr & (RTSR_ALE | RTSR_HZE)) {
		/* This is the original code, before there was the if test
		 * above. This code does not clear interrupts that were not
		 * enabled. */
		writel_relaxed((RTSR_AL | RTSR_HZ) & (rtsr >> 2), info->rtsr);
	} else {
		/* For some reason, it is possible to enter this routine
		 * without interruptions enabled, it has been tested with
		 * several units (Bug in SA11xx chip?).
		 *
		 * This situation leads to an infinite "loop" of interrupt
		 * routine calling and as a result the processor seems to
		 * lock on its first call to open(). */
		writel_relaxed(RTSR_AL | RTSR_HZ, info->rtsr);
	}

	/* clear alarm interrupt if it has occurred */
	if (rtsr & RTSR_AL)
		rtsr &= ~RTSR_ALE;
	writel_relaxed(rtsr & (RTSR_ALE | RTSR_HZE), info->rtsr);

	/* update irq data & counter */
	if (rtsr & RTSR_AL)
		events |= RTC_AF | RTC_IRQF;
	if (rtsr & RTSR_HZ)
		events |= RTC_UF | RTC_IRQF;

	rtc_update_irq(rtc, 1, events);

	spin_unlock(&info->lock);

	return IRQ_HANDLED;
}