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
struct rtc_time {int dummy; } ;
struct omap_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcd2tm (struct rtc_time*) ; 
 struct omap_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  omap_rtc_read_time_raw (struct omap_rtc*,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_wait_not_busy (struct omap_rtc*) ; 

__attribute__((used)) static int omap_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct omap_rtc *rtc = dev_get_drvdata(dev);

	/* we don't report wday/yday/isdst ... */
	local_irq_disable();
	rtc_wait_not_busy(rtc);
	omap_rtc_read_time_raw(rtc, tm);
	local_irq_enable();

	bcd2tm(tm);

	return 0;
}