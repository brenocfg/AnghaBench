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
typedef  int u8 ;
struct TYPE_2__ {void* tm_year; void* tm_mon; void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; TYPE_1__ time; } ;
struct omap_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_RTC_ALARM_DAYS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_HOURS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_MINUTES_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_MONTHS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_SECONDS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM_YEARS_REG ; 
 int OMAP_RTC_INTERRUPTS_IT_ALARM ; 
 int /*<<< orphan*/  OMAP_RTC_INTERRUPTS_REG ; 
 int /*<<< orphan*/  bcd2tm (TYPE_1__*) ; 
 struct omap_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 void* rtc_read (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_wait_not_busy (struct omap_rtc*) ; 

__attribute__((used)) static int omap_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alm)
{
	struct omap_rtc *rtc = dev_get_drvdata(dev);
	u8 interrupts;

	local_irq_disable();
	rtc_wait_not_busy(rtc);

	alm->time.tm_sec = rtc_read(rtc, OMAP_RTC_ALARM_SECONDS_REG);
	alm->time.tm_min = rtc_read(rtc, OMAP_RTC_ALARM_MINUTES_REG);
	alm->time.tm_hour = rtc_read(rtc, OMAP_RTC_ALARM_HOURS_REG);
	alm->time.tm_mday = rtc_read(rtc, OMAP_RTC_ALARM_DAYS_REG);
	alm->time.tm_mon = rtc_read(rtc, OMAP_RTC_ALARM_MONTHS_REG);
	alm->time.tm_year = rtc_read(rtc, OMAP_RTC_ALARM_YEARS_REG);

	local_irq_enable();

	bcd2tm(&alm->time);

	interrupts = rtc_read(rtc, OMAP_RTC_INTERRUPTS_REG);
	alm->enabled = !!(interrupts & OMAP_RTC_INTERRUPTS_IT_ALARM);

	return 0;
}