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
typedef  int u32 ;
struct armada38x_rtc {int initialized; TYPE_1__* data; } ;
struct TYPE_2__ {int (* read_rtc_reg ) (struct armada38x_rtc*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CCR ; 
 int /*<<< orphan*/  RTC_CONF_TEST ; 
 int RTC_NOMINAL_TIMING ; 
 int /*<<< orphan*/  RTC_STATUS ; 
 int /*<<< orphan*/  RTC_TIME ; 
 int SOC_RTC_ALARM1 ; 
 int SOC_RTC_ALARM2 ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rtc_delayed_write (int,struct armada38x_rtc*,int /*<<< orphan*/ ) ; 
 int stub1 (struct armada38x_rtc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void armada38x_rtc_reset(struct armada38x_rtc *rtc)
{
	u32 reg;

	reg = rtc->data->read_rtc_reg(rtc, RTC_CONF_TEST);
	/* If bits [7:0] are non-zero, assume RTC was uninitialized */
	if (reg & 0xff) {
		rtc_delayed_write(0, rtc, RTC_CONF_TEST);
		msleep(500); /* Oscillator startup time */
		rtc_delayed_write(0, rtc, RTC_TIME);
		rtc_delayed_write(SOC_RTC_ALARM1 | SOC_RTC_ALARM2, rtc,
				  RTC_STATUS);
		rtc_delayed_write(RTC_NOMINAL_TIMING, rtc, RTC_CCR);
	}
	rtc->initialized = true;
}