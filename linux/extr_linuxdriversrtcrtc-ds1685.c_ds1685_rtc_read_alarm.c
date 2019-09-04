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
struct TYPE_2__ {void* tm_mday; void* tm_hour; void* tm_min; void* tm_sec; } ;
struct rtc_wkalrm {int enabled; int pending; TYPE_1__ time; } ;
struct ds1685_priv {int (* read ) (struct ds1685_priv*,int /*<<< orphan*/ ) ;} ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTC_CTRL_B ; 
 int RTC_CTRL_B_AIE ; 
 int /*<<< orphan*/  RTC_CTRL_C ; 
 int RTC_CTRL_C_AF ; 
 int /*<<< orphan*/  RTC_HRS_24_BCD_MASK ; 
 int /*<<< orphan*/  RTC_HRS_24_BIN_MASK ; 
 int /*<<< orphan*/  RTC_HRS_ALARM ; 
 int /*<<< orphan*/  RTC_MDAY_ALARM ; 
 int /*<<< orphan*/  RTC_MDAY_BCD_MASK ; 
 int /*<<< orphan*/  RTC_MDAY_BIN_MASK ; 
 int /*<<< orphan*/  RTC_MINS_ALARM ; 
 int /*<<< orphan*/  RTC_MINS_BCD_MASK ; 
 int /*<<< orphan*/  RTC_MINS_BIN_MASK ; 
 int /*<<< orphan*/  RTC_SECS_ALARM ; 
 int /*<<< orphan*/  RTC_SECS_BCD_MASK ; 
 int /*<<< orphan*/  RTC_SECS_BIN_MASK ; 
 struct ds1685_priv* dev_get_drvdata (struct device*) ; 
 void* ds1685_rtc_bcd2bin (struct ds1685_priv*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds1685_rtc_begin_data_access (struct ds1685_priv*) ; 
 int ds1685_rtc_check_mday (struct ds1685_priv*,int) ; 
 int /*<<< orphan*/  ds1685_rtc_end_data_access (struct ds1685_priv*) ; 
 scalar_t__ likely (int) ; 
 int stub1 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub2 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub3 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub4 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub5 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 
 int stub6 (struct ds1685_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ds1685_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct ds1685_priv *rtc = dev_get_drvdata(dev);
	u8 seconds, minutes, hours, mday, ctrlb, ctrlc;
	int ret;

	/* Fetch the alarm info from the RTC alarm registers. */
	ds1685_rtc_begin_data_access(rtc);
	seconds	= rtc->read(rtc, RTC_SECS_ALARM);
	minutes	= rtc->read(rtc, RTC_MINS_ALARM);
	hours	= rtc->read(rtc, RTC_HRS_ALARM);
	mday	= rtc->read(rtc, RTC_MDAY_ALARM);
	ctrlb	= rtc->read(rtc, RTC_CTRL_B);
	ctrlc	= rtc->read(rtc, RTC_CTRL_C);
	ds1685_rtc_end_data_access(rtc);

	/* Check the month date for validity. */
	ret = ds1685_rtc_check_mday(rtc, mday);
	if (ret)
		return ret;

	/*
	 * Check the three alarm bytes.
	 *
	 * The Linux RTC system doesn't support the "don't care" capability
	 * of this RTC chip.  We check for it anyways in case support is
	 * added in the future and only assign when we care.
	 */
	if (likely(seconds < 0xc0))
		alrm->time.tm_sec = ds1685_rtc_bcd2bin(rtc, seconds,
						       RTC_SECS_BCD_MASK,
						       RTC_SECS_BIN_MASK);

	if (likely(minutes < 0xc0))
		alrm->time.tm_min = ds1685_rtc_bcd2bin(rtc, minutes,
						       RTC_MINS_BCD_MASK,
						       RTC_MINS_BIN_MASK);

	if (likely(hours < 0xc0))
		alrm->time.tm_hour = ds1685_rtc_bcd2bin(rtc, hours,
							RTC_HRS_24_BCD_MASK,
							RTC_HRS_24_BIN_MASK);

	/* Write the data to rtc_wkalrm. */
	alrm->time.tm_mday = ds1685_rtc_bcd2bin(rtc, mday, RTC_MDAY_BCD_MASK,
						RTC_MDAY_BIN_MASK);
	alrm->enabled = !!(ctrlb & RTC_CTRL_B_AIE);
	alrm->pending = !!(ctrlc & RTC_CTRL_C_AF);

	return 0;
}