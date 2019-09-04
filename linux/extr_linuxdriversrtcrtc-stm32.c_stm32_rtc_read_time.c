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
struct stm32_rtc_registers {int /*<<< orphan*/  dr; int /*<<< orphan*/  tr; } ;
struct stm32_rtc {scalar_t__ base; TYPE_1__* data; } ;
struct rtc_time {unsigned int tm_sec; unsigned int tm_min; unsigned int tm_hour; unsigned int tm_mday; unsigned int tm_mon; unsigned int tm_year; unsigned int tm_wday; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 unsigned int STM32_RTC_DR_DATE ; 
 unsigned int STM32_RTC_DR_DATE_SHIFT ; 
 unsigned int STM32_RTC_DR_MONTH ; 
 unsigned int STM32_RTC_DR_MONTH_SHIFT ; 
 unsigned int STM32_RTC_DR_WDAY ; 
 unsigned int STM32_RTC_DR_WDAY_SHIFT ; 
 unsigned int STM32_RTC_DR_YEAR ; 
 unsigned int STM32_RTC_DR_YEAR_SHIFT ; 
 unsigned int STM32_RTC_TR_HOUR ; 
 unsigned int STM32_RTC_TR_HOUR_SHIFT ; 
 unsigned int STM32_RTC_TR_MIN ; 
 unsigned int STM32_RTC_TR_MIN_SHIFT ; 
 unsigned int STM32_RTC_TR_SEC ; 
 unsigned int STM32_RTC_TR_SEC_SHIFT ; 
 int /*<<< orphan*/  bcd2tm (struct rtc_time*) ; 
 struct stm32_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct stm32_rtc *rtc = dev_get_drvdata(dev);
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	unsigned int tr, dr;

	/* Time and Date in BCD format */
	tr = readl_relaxed(rtc->base + regs->tr);
	dr = readl_relaxed(rtc->base + regs->dr);

	tm->tm_sec = (tr & STM32_RTC_TR_SEC) >> STM32_RTC_TR_SEC_SHIFT;
	tm->tm_min = (tr & STM32_RTC_TR_MIN) >> STM32_RTC_TR_MIN_SHIFT;
	tm->tm_hour = (tr & STM32_RTC_TR_HOUR) >> STM32_RTC_TR_HOUR_SHIFT;

	tm->tm_mday = (dr & STM32_RTC_DR_DATE) >> STM32_RTC_DR_DATE_SHIFT;
	tm->tm_mon = (dr & STM32_RTC_DR_MONTH) >> STM32_RTC_DR_MONTH_SHIFT;
	tm->tm_year = (dr & STM32_RTC_DR_YEAR) >> STM32_RTC_DR_YEAR_SHIFT;
	tm->tm_wday = (dr & STM32_RTC_DR_WDAY) >> STM32_RTC_DR_WDAY_SHIFT;

	/* We don't report tm_yday and tm_isdst */

	bcd2tm(tm);

	return 0;
}