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
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct stm32_rtc* dev_get_drvdata (struct device*) ; 
 int stm32_rtc_enter_init_mode (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_exit_init_mode (struct stm32_rtc*) ; 
 int stm32_rtc_wait_sync (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_lock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  stm32_rtc_wpr_unlock (struct stm32_rtc*) ; 
 int /*<<< orphan*/  tm2bcd (struct rtc_time*) ; 
 int /*<<< orphan*/  writel_relaxed (unsigned int,scalar_t__) ; 

__attribute__((used)) static int stm32_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct stm32_rtc *rtc = dev_get_drvdata(dev);
	const struct stm32_rtc_registers *regs = &rtc->data->regs;
	unsigned int tr, dr;
	int ret = 0;

	tm2bcd(tm);

	/* Time in BCD format */
	tr = ((tm->tm_sec << STM32_RTC_TR_SEC_SHIFT) & STM32_RTC_TR_SEC) |
	     ((tm->tm_min << STM32_RTC_TR_MIN_SHIFT) & STM32_RTC_TR_MIN) |
	     ((tm->tm_hour << STM32_RTC_TR_HOUR_SHIFT) & STM32_RTC_TR_HOUR);

	/* Date in BCD format */
	dr = ((tm->tm_mday << STM32_RTC_DR_DATE_SHIFT) & STM32_RTC_DR_DATE) |
	     ((tm->tm_mon << STM32_RTC_DR_MONTH_SHIFT) & STM32_RTC_DR_MONTH) |
	     ((tm->tm_year << STM32_RTC_DR_YEAR_SHIFT) & STM32_RTC_DR_YEAR) |
	     ((tm->tm_wday << STM32_RTC_DR_WDAY_SHIFT) & STM32_RTC_DR_WDAY);

	stm32_rtc_wpr_unlock(rtc);

	ret = stm32_rtc_enter_init_mode(rtc);
	if (ret) {
		dev_err(dev, "Can't enter in init mode. Set time aborted.\n");
		goto end;
	}

	writel_relaxed(tr, rtc->base + regs->tr);
	writel_relaxed(dr, rtc->base + regs->dr);

	stm32_rtc_exit_init_mode(rtc);

	ret = stm32_rtc_wait_sync(rtc);
end:
	stm32_rtc_wpr_lock(rtc);

	return ret;
}