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
typedef  scalar_t__ time64_t ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct mxc_rtc_data {scalar_t__ ioaddr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ SRTC_LPSAR ; 
 scalar_t__ SRTC_LPSR ; 
 int /*<<< orphan*/  SRTC_LPSR_ALP ; 
 struct mxc_rtc_data* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  mxc_rtc_alarm_irq_enable_locked (struct mxc_rtc_data*,int /*<<< orphan*/ ) ; 
 int mxc_rtc_lock (struct mxc_rtc_data*) ; 
 int /*<<< orphan*/  mxc_rtc_sync_lp_locked (struct device*,scalar_t__) ; 
 int /*<<< orphan*/  mxc_rtc_unlock (struct mxc_rtc_data*) ; 
 scalar_t__ rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mxc_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	const time64_t time = rtc_tm_to_time64(&alrm->time);
	struct mxc_rtc_data *pdata = dev_get_drvdata(dev);
	int ret = mxc_rtc_lock(pdata);

	if (ret)
		return ret;

	writel((u32)time, pdata->ioaddr + SRTC_LPSAR);

	/* clear alarm interrupt status bit */
	writel(SRTC_LPSR_ALP, pdata->ioaddr + SRTC_LPSR);
	mxc_rtc_sync_lp_locked(dev, pdata->ioaddr);

	mxc_rtc_alarm_irq_enable_locked(pdata, alrm->enabled);
	mxc_rtc_sync_lp_locked(dev, pdata->ioaddr);
	mxc_rtc_unlock(pdata);
	return ret;
}