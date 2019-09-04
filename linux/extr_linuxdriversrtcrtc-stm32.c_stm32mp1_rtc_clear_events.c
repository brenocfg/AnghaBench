#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stm32_rtc_registers {scalar_t__ scr; } ;
struct stm32_rtc {scalar_t__ base; TYPE_1__* data; } ;
struct TYPE_2__ {struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static void stm32mp1_rtc_clear_events(struct stm32_rtc *rtc,
				      unsigned int flags)
{
	struct stm32_rtc_registers regs = rtc->data->regs;

	/* Flags are cleared by writing 1 in RTC_SCR */
	writel_relaxed(flags, rtc->base + regs.scr);
}