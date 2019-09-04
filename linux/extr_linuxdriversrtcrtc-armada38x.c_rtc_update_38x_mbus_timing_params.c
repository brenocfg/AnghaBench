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
 scalar_t__ RTC_38X_BRIDGE_TIMING_CTL ; 
 int RTC_38X_PERIOD_MASK ; 
 int RTC_38X_PERIOD_OFFS ; 
 int RTC_38X_READ_DELAY_MASK ; 
 int RTC_38X_READ_DELAY_OFFS ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void rtc_update_38x_mbus_timing_params(struct armada38x_rtc *rtc)
{
	u32 reg;

	reg = readl(rtc->regs_soc + RTC_38X_BRIDGE_TIMING_CTL);
	reg &= ~RTC_38X_PERIOD_MASK;
	reg |= 0x3FF << RTC_38X_PERIOD_OFFS; /* Maximum value */
	reg &= ~RTC_38X_READ_DELAY_MASK;
	reg |= 0x1F << RTC_38X_READ_DELAY_OFFS; /* Maximum value */
	writel(reg, rtc->regs_soc + RTC_38X_BRIDGE_TIMING_CTL);
}