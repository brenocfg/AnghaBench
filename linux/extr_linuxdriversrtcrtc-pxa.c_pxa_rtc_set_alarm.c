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
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct pxa_rtc {int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDAR1 ; 
 int /*<<< orphan*/  RTSR ; 
 int /*<<< orphan*/  RTSR_RDALE1 ; 
 int /*<<< orphan*/  RYAR1 ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rdxr_calc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtc_readl (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_writel (struct pxa_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ryxr_calc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	u32 rtsr;

	spin_lock_irq(&pxa_rtc->lock);

	rtc_writel(pxa_rtc, RYAR1, ryxr_calc(&alrm->time));
	rtc_writel(pxa_rtc, RDAR1, rdxr_calc(&alrm->time));

	rtsr = rtc_readl(pxa_rtc, RTSR);
	if (alrm->enabled)
		rtsr |= RTSR_RDALE1;
	else
		rtsr &= ~RTSR_RDALE1;
	rtc_writel(pxa_rtc, RTSR, rtsr);

	spin_unlock_irq(&pxa_rtc->lock);

	return 0;
}