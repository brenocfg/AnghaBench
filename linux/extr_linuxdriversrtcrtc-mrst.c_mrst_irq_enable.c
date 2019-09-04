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
struct mrst_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  mrst_checkintr (struct mrst_rtc*,unsigned char) ; 
 unsigned char vrtc_cmos_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrtc_cmos_write (unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mrst_irq_enable(struct mrst_rtc *mrst, unsigned char mask)
{
	unsigned char	rtc_control;

	/*
	 * Flush any pending IRQ status, notably for update irqs,
	 * before we enable new IRQs
	 */
	rtc_control = vrtc_cmos_read(RTC_CONTROL);
	mrst_checkintr(mrst, rtc_control);

	rtc_control |= mask;
	vrtc_cmos_write(rtc_control, RTC_CONTROL);

	mrst_checkintr(mrst, rtc_control);
}