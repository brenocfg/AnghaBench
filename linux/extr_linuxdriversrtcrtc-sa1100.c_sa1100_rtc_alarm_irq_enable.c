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
struct sa1100_rtc {int /*<<< orphan*/  lock; int /*<<< orphan*/  rtsr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTSR_ALE ; 
 struct sa1100_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	u32 rtsr;
	struct sa1100_rtc *info = dev_get_drvdata(dev);

	spin_lock_irq(&info->lock);
	rtsr = readl_relaxed(info->rtsr);
	if (enabled)
		rtsr |= RTSR_ALE;
	else
		rtsr &= ~RTSR_ALE;
	writel_relaxed(rtsr, info->rtsr);
	spin_unlock_irq(&info->lock);
	return 0;
}