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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ time64_t ;
struct rtc_wkalrm {int /*<<< orphan*/  enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;
struct dc_rtc {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ DC_RTC_ALARM ; 
 scalar_t__ DC_RTC_INTENABLE ; 
 scalar_t__ DC_RTC_REFERENCE ; 
 struct dc_rtc* dev_get_drvdata (struct device*) ; 
 scalar_t__ readl_relaxed (scalar_t__) ; 
 scalar_t__ rtc_tm_to_time64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb_relaxed (int,scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int dc_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alarm)
{
	struct dc_rtc *rtc = dev_get_drvdata(dev);
	time64_t alarm_time;
	u32 reference;

	alarm_time = rtc_tm_to_time64(&alarm->time);

	reference = readl_relaxed(rtc->regs + DC_RTC_REFERENCE);
	writel_relaxed(alarm_time - reference, rtc->regs + DC_RTC_ALARM);

	writeb_relaxed(!!alarm->enabled, rtc->regs + DC_RTC_INTENABLE);

	return 0;
}