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
struct sam9_rtc {int /*<<< orphan*/  lock; scalar_t__ suspended; } ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int AT91_RTT_ALMIEN ; 
 int AT91_RTT_RTTINCIEN ; 
 int /*<<< orphan*/  MR ; 
 int at91_rtc_cache_events (struct sam9_rtc*) ; 
 int /*<<< orphan*/  at91_rtc_flush_events (struct sam9_rtc*) ; 
 int /*<<< orphan*/  pm_system_wakeup () ; 
 int rtt_readl (struct sam9_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtt_writel (struct sam9_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t at91_rtc_interrupt(int irq, void *_rtc)
{
	struct sam9_rtc *rtc = _rtc;
	int ret;

	spin_lock(&rtc->lock);

	ret = at91_rtc_cache_events(rtc);

	/* We're called in suspended state */
	if (rtc->suspended) {
		/* Mask irqs coming from this peripheral */
		rtt_writel(rtc, MR,
			   rtt_readl(rtc, MR) &
			   ~(AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN));
		/* Trigger a system wakeup */
		pm_system_wakeup();
	} else {
		at91_rtc_flush_events(rtc);
	}

	spin_unlock(&rtc->lock);

	return ret;
}