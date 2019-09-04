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
typedef  scalar_t__ u32 ;
struct xgene_rtc_dev {scalar_t__ csr_base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ RTC_CCR ; 
 scalar_t__ RTC_CCR_IE ; 
 scalar_t__ RTC_CCR_MASK ; 
 struct xgene_rtc_dev* dev_get_drvdata (struct device*) ; 
 scalar_t__ readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int xgene_rtc_alarm_irq_enable(struct device *dev, u32 enabled)
{
	struct xgene_rtc_dev *pdata = dev_get_drvdata(dev);
	u32 ccr;

	ccr = readl(pdata->csr_base + RTC_CCR);
	if (enabled) {
		ccr &= ~RTC_CCR_MASK;
		ccr |= RTC_CCR_IE;
	} else {
		ccr &= ~RTC_CCR_IE;
		ccr |= RTC_CCR_MASK;
	}
	writel(ccr, pdata->csr_base + RTC_CCR);

	return 0;
}