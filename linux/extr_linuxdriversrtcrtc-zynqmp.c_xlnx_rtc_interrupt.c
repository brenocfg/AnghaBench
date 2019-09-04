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
struct xlnx_rtc_dev {int /*<<< orphan*/  rtc; scalar_t__ reg_base; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AF ; 
 unsigned int RTC_INT_ALRM ; 
 unsigned int RTC_INT_SEC ; 
 scalar_t__ RTC_INT_STS ; 
 int RTC_IRQF ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t xlnx_rtc_interrupt(int irq, void *id)
{
	struct xlnx_rtc_dev *xrtcdev = (struct xlnx_rtc_dev *)id;
	unsigned int status;

	status = readl(xrtcdev->reg_base + RTC_INT_STS);
	/* Check if interrupt asserted */
	if (!(status & (RTC_INT_SEC | RTC_INT_ALRM)))
		return IRQ_NONE;

	/* Clear RTC_INT_ALRM interrupt only */
	writel(RTC_INT_ALRM, xrtcdev->reg_base + RTC_INT_STS);

	if (status & RTC_INT_ALRM)
		rtc_update_irq(xrtcdev->rtc, 1, RTC_IRQF | RTC_AF);

	return IRQ_HANDLED;
}