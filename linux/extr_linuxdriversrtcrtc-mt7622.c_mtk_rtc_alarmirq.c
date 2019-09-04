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
struct mtk_rtc {int /*<<< orphan*/  rtc; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  MTK_RTC_AL_CTL ; 
 int /*<<< orphan*/  MTK_RTC_INT ; 
 int RTC_AF ; 
 int RTC_INT_AL_STA ; 
 int RTC_IRQF ; 
 int mtk_r32 (struct mtk_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtk_w32 (struct mtk_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static irqreturn_t mtk_rtc_alarmirq(int irq, void *id)
{
	struct mtk_rtc *hw = (struct mtk_rtc *)id;
	u32 irq_sta;

	irq_sta = mtk_r32(hw, MTK_RTC_INT);
	if (irq_sta & RTC_INT_AL_STA) {
		/* Stop alarm also implicitly disables the alarm interrupt */
		mtk_w32(hw, MTK_RTC_AL_CTL, 0);
		rtc_update_irq(hw->rtc, 1, RTC_IRQF | RTC_AF);

		/* Ack alarm interrupt status */
		mtk_w32(hw, MTK_RTC_INT, RTC_INT_AL_STA);
		return IRQ_HANDLED;
	}

	return IRQ_NONE;
}