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
struct sa1100_rtc {int /*<<< orphan*/  lock; int /*<<< orphan*/  rtsr; int /*<<< orphan*/  rtar; } ;
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned long RTSR_AL ; 
 unsigned long RTSR_ALE ; 
 unsigned long RTSR_HZE ; 
 struct sa1100_rtc* dev_get_drvdata (struct device*) ; 
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 
 int rtc_tm_to_time (int /*<<< orphan*/ *,unsigned long*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sa1100_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct sa1100_rtc *info = dev_get_drvdata(dev);
	unsigned long time;
	int ret;

	spin_lock_irq(&info->lock);
	ret = rtc_tm_to_time(&alrm->time, &time);
	if (ret != 0)
		goto out;
	writel_relaxed(readl_relaxed(info->rtsr) &
		(RTSR_HZE | RTSR_ALE | RTSR_AL), info->rtsr);
	writel_relaxed(time, info->rtar);
	if (alrm->enabled)
		writel_relaxed(readl_relaxed(info->rtsr) | RTSR_ALE, info->rtsr);
	else
		writel_relaxed(readl_relaxed(info->rtsr) & ~RTSR_ALE, info->rtsr);
out:
	spin_unlock_irq(&info->lock);

	return ret;
}