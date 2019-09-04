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
struct armada38x_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ RTC_STATUS ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void rtc_delayed_write(u32 val, struct armada38x_rtc *rtc, int offset)
{
	writel(0, rtc->regs + RTC_STATUS);
	writel(0, rtc->regs + RTC_STATUS);
	writel(val, rtc->regs + offset);
	udelay(5);
}