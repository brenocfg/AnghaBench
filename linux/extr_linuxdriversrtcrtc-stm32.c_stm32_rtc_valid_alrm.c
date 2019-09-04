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
struct stm32_rtc_registers {int /*<<< orphan*/  tr; int /*<<< orphan*/  dr; } ;
struct stm32_rtc {scalar_t__ base; TYPE_1__* data; } ;
struct rtc_time {int tm_year; int tm_mon; int tm_mday; int tm_hour; int tm_min; int tm_sec; } ;
struct TYPE_2__ {struct stm32_rtc_registers regs; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int STM32_RTC_DR_DATE ; 
 unsigned int STM32_RTC_DR_DATE_SHIFT ; 
 unsigned int STM32_RTC_DR_MONTH ; 
 unsigned int STM32_RTC_DR_MONTH_SHIFT ; 
 unsigned int STM32_RTC_DR_YEAR ; 
 unsigned int STM32_RTC_DR_YEAR_SHIFT ; 
 unsigned int STM32_RTC_TR_HOUR ; 
 unsigned int STM32_RTC_TR_HOUR_SHIFT ; 
 unsigned int STM32_RTC_TR_MIN ; 
 unsigned int STM32_RTC_TR_MIN_SHIFT ; 
 unsigned int STM32_RTC_TR_SEC ; 
 unsigned int STM32_RTC_TR_SEC_SHIFT ; 
 unsigned int readl_relaxed (scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_valid_alrm(struct stm32_rtc *rtc, struct rtc_time *tm)
{
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	int cur_day, cur_mon, cur_year, cur_hour, cur_min, cur_sec;
	unsigned int dr = readl_relaxed(rtc->base + regs->dr);
	unsigned int tr = readl_relaxed(rtc->base + regs->tr);

	cur_day = (dr & STM32_RTC_DR_DATE) >> STM32_RTC_DR_DATE_SHIFT;
	cur_mon = (dr & STM32_RTC_DR_MONTH) >> STM32_RTC_DR_MONTH_SHIFT;
	cur_year = (dr & STM32_RTC_DR_YEAR) >> STM32_RTC_DR_YEAR_SHIFT;
	cur_sec = (tr & STM32_RTC_TR_SEC) >> STM32_RTC_TR_SEC_SHIFT;
	cur_min = (tr & STM32_RTC_TR_MIN) >> STM32_RTC_TR_MIN_SHIFT;
	cur_hour = (tr & STM32_RTC_TR_HOUR) >> STM32_RTC_TR_HOUR_SHIFT;

	/*
	 * Assuming current date is M-D-Y H:M:S.
	 * RTC alarm can't be set on a specific month and year.
	 * So the valid alarm range is:
	 *	M-D-Y H:M:S < alarm <= (M+1)-D-Y H:M:S
	 * with a specific case for December...
	 */
	if ((((tm->tm_year > cur_year) &&
	      (tm->tm_mon == 0x1) && (cur_mon == 0x12)) ||
	     ((tm->tm_year == cur_year) &&
	      (tm->tm_mon <= cur_mon + 1))) &&
	    ((tm->tm_mday > cur_day) ||
	     ((tm->tm_mday == cur_day) &&
	     ((tm->tm_hour > cur_hour) ||
	      ((tm->tm_hour == cur_hour) && (tm->tm_min > cur_min)) ||
	      ((tm->tm_hour == cur_hour) && (tm->tm_min == cur_min) &&
	       (tm->tm_sec >= cur_sec))))))
		return 0;

	return -EINVAL;
}