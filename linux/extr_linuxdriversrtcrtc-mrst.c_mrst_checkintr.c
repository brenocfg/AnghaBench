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
struct mrst_rtc {int /*<<< orphan*/  rtc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_INTR_FLAGS ; 
 unsigned char RTC_IRQF ; 
 unsigned char RTC_IRQMASK ; 
 scalar_t__ is_intr (unsigned char) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned char) ; 
 unsigned char vrtc_cmos_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mrst_checkintr(struct mrst_rtc *mrst, unsigned char rtc_control)
{
	unsigned char	rtc_intr;

	/*
	 * NOTE after changing RTC_xIE bits we always read INTR_FLAGS;
	 * allegedly some older rtcs need that to handle irqs properly
	 */
	rtc_intr = vrtc_cmos_read(RTC_INTR_FLAGS);
	rtc_intr &= (rtc_control & RTC_IRQMASK) | RTC_IRQF;
	if (is_intr(rtc_intr))
		rtc_update_irq(mrst->rtc, 1, rtc_intr);
}