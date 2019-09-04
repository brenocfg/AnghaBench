#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rtc_time {int /*<<< orphan*/  tm_year; int /*<<< orphan*/  tm_mon; int /*<<< orphan*/  tm_mday; int /*<<< orphan*/  tm_hour; int /*<<< orphan*/  tm_min; int /*<<< orphan*/  tm_sec; } ;
struct omap_rtc {TYPE_2__* type; TYPE_1__* rtc; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* lock ) (struct omap_rtc*) ;int /*<<< orphan*/  (* unlock ) (struct omap_rtc*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_RTC_ALARM2_DAYS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_HOURS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_MINUTES_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_MONTHS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_SECONDS_REG ; 
 int /*<<< orphan*/  OMAP_RTC_ALARM2_YEARS_REG ; 
 int OMAP_RTC_INTERRUPTS_IT_ALARM2 ; 
 int /*<<< orphan*/  OMAP_RTC_INTERRUPTS_REG ; 
 int OMAP_RTC_PMIC_POWER_EN_EN ; 
 int /*<<< orphan*/  OMAP_RTC_PMIC_REG ; 
 int /*<<< orphan*/  bcd2tm (struct rtc_time*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct omap_rtc* omap_rtc_power_off_rtc ; 
 int /*<<< orphan*/  omap_rtc_read_time_raw (struct omap_rtc*,struct rtc_time*) ; 
 int rtc_read (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int rtc_readl (struct omap_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_time_to_tm (unsigned long,struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_tm_to_time (struct rtc_time*,unsigned long*) ; 
 int /*<<< orphan*/  rtc_wait_not_busy (struct omap_rtc*) ; 
 int /*<<< orphan*/  rtc_write (struct omap_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_writel (struct omap_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub2 (struct omap_rtc*) ; 
 int /*<<< orphan*/  stub3 (struct omap_rtc*) ; 
 scalar_t__ tm2bcd (struct rtc_time*) ; 

__attribute__((used)) static void omap_rtc_power_off(void)
{
	struct omap_rtc *rtc = omap_rtc_power_off_rtc;
	struct rtc_time tm;
	unsigned long now;
	u32 val;

	rtc->type->unlock(rtc);
	/* enable pmic_power_en control */
	val = rtc_readl(rtc, OMAP_RTC_PMIC_REG);
	rtc_writel(rtc, OMAP_RTC_PMIC_REG, val | OMAP_RTC_PMIC_POWER_EN_EN);

	/* set alarm two seconds from now */
	omap_rtc_read_time_raw(rtc, &tm);
	bcd2tm(&tm);
	rtc_tm_to_time(&tm, &now);
	rtc_time_to_tm(now + 2, &tm);

	if (tm2bcd(&tm) < 0) {
		dev_err(&rtc->rtc->dev, "power off failed\n");
		rtc->type->lock(rtc);
		return;
	}

	rtc_wait_not_busy(rtc);

	rtc_write(rtc, OMAP_RTC_ALARM2_SECONDS_REG, tm.tm_sec);
	rtc_write(rtc, OMAP_RTC_ALARM2_MINUTES_REG, tm.tm_min);
	rtc_write(rtc, OMAP_RTC_ALARM2_HOURS_REG, tm.tm_hour);
	rtc_write(rtc, OMAP_RTC_ALARM2_DAYS_REG, tm.tm_mday);
	rtc_write(rtc, OMAP_RTC_ALARM2_MONTHS_REG, tm.tm_mon);
	rtc_write(rtc, OMAP_RTC_ALARM2_YEARS_REG, tm.tm_year);

	/*
	 * enable ALARM2 interrupt
	 *
	 * NOTE: this fails on AM3352 if rtc_write (writeb) is used
	 */
	val = rtc_read(rtc, OMAP_RTC_INTERRUPTS_REG);
	rtc_writel(rtc, OMAP_RTC_INTERRUPTS_REG,
			val | OMAP_RTC_INTERRUPTS_IT_ALARM2);
	rtc->type->lock(rtc);

	/*
	 * Wait for alarm to trigger (within two seconds) and external PMIC to
	 * power off the system. Add a 500 ms margin for external latencies
	 * (e.g. debounce circuits).
	 */
	mdelay(2500);
}