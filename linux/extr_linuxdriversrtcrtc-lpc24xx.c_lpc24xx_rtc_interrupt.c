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
struct lpc24xx_rtc {int /*<<< orphan*/  rtc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int LPC24XX_ALARM_DISABLE ; 
 int /*<<< orphan*/  LPC24XX_AMR ; 
 int /*<<< orphan*/  LPC24XX_ILR ; 
 int LPC24XX_RTCALF ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 int rtc_readl (struct lpc24xx_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  rtc_writel (struct lpc24xx_rtc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t lpc24xx_rtc_interrupt(int irq, void *data)
{
	unsigned long events = RTC_IRQF;
	struct lpc24xx_rtc *rtc = data;
	u32 rtc_iir;

	/* Check interrupt cause */
	rtc_iir = rtc_readl(rtc, LPC24XX_ILR);
	if (rtc_iir & LPC24XX_RTCALF) {
		events |= RTC_AF;
		rtc_writel(rtc, LPC24XX_AMR, LPC24XX_ALARM_DISABLE);
	}

	/* Clear interrupt status and report event */
	rtc_writel(rtc, LPC24XX_ILR, rtc_iir);
	rtc_update_irq(rtc->rtc, 1, events);

	return IRQ_HANDLED;
}