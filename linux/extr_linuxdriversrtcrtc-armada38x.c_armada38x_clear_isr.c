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
struct armada38x_rtc {scalar_t__ regs_soc; } ;

/* Variables and functions */
 int SOC_RTC_ALARM1 ; 
 scalar_t__ SOC_RTC_INTERRUPT ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void armada38x_clear_isr(struct armada38x_rtc *rtc)
{
	u32 val = readl(rtc->regs_soc + SOC_RTC_INTERRUPT);

	writel(val & ~SOC_RTC_ALARM1, rtc->regs_soc + SOC_RTC_INTERRUPT);
}