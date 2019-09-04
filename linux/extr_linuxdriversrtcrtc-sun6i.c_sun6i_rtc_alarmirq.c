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
typedef  int u32 ;
struct sun6i_rtc_dev {int /*<<< orphan*/  lock; int /*<<< orphan*/  rtc; scalar_t__ base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 scalar_t__ SUN6I_ALRM_IRQ_STA ; 
 int SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t sun6i_rtc_alarmirq(int irq, void *id)
{
	struct sun6i_rtc_dev *chip = (struct sun6i_rtc_dev *) id;
	irqreturn_t ret = IRQ_NONE;
	u32 val;

	spin_lock(&chip->lock);
	val = readl(chip->base + SUN6I_ALRM_IRQ_STA);

	if (val & SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND) {
		val |= SUN6I_ALRM_IRQ_STA_CNT_IRQ_PEND;
		writel(val, chip->base + SUN6I_ALRM_IRQ_STA);

		rtc_update_irq(chip->rtc, 1, RTC_AF | RTC_IRQF);

		ret = IRQ_HANDLED;
	}
	spin_unlock(&chip->lock);

	return ret;
}