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
struct stm32_rtc_registers {int /*<<< orphan*/  isr; } ;
struct stm32_rtc {scalar_t__ base; TYPE_1__* data; } ;
struct TYPE_2__ {struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 unsigned int STM32_RTC_ISR_RSF ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 int readl_relaxed_poll_timeout_atomic (scalar_t__,unsigned int,unsigned int,int,int) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_wait_sync(struct stm32_rtc *rtc)
{
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	unsigned int isr = readl_relaxed(rtc->base + regs->isr);

	isr &= ~STM32_RTC_ISR_RSF;
	writel_relaxed(isr, rtc->base + regs->isr);

	/*
	 * Wait for RSF to be set to ensure the calendar registers are
	 * synchronised, it takes around 2 rtc_ck clock cycles
	 */
	return readl_relaxed_poll_timeout_atomic(rtc->base + regs->isr,
						 isr,
						 (isr & STM32_RTC_ISR_RSF),
						 10, 100000);
}