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
typedef  int /*<<< orphan*/  u8 ;
struct rtc_time {int tm_sec; int tm_min; int tm_hour; int tm_mday; int tm_mon; int tm_year; int tm_wday; } ;
struct fm3130 {int data_valid; int /*<<< orphan*/ * regs; int /*<<< orphan*/  client; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int FM3130_CLOCK_REGS ; 
 int /*<<< orphan*/  FM3130_MODE_NORMAL ; 
 int /*<<< orphan*/  FM3130_MODE_WRITE ; 
 size_t FM3130_RTC_DATE ; 
 size_t FM3130_RTC_DAY ; 
 size_t FM3130_RTC_HOURS ; 
 size_t FM3130_RTC_MINUTES ; 
 size_t FM3130_RTC_MONTHS ; 
 size_t FM3130_RTC_SECONDS ; 
 size_t FM3130_RTC_YEARS ; 
 int /*<<< orphan*/  bin2bcd (int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char*,int,...) ; 
 struct fm3130* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fm3130_rtc_mode (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_smbus_write_byte_data (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fm3130_set_time(struct device *dev, struct rtc_time *t)
{
	struct fm3130 *fm3130 = dev_get_drvdata(dev);
	int		tmp, i;
	u8		*buf = fm3130->regs;

	dev_dbg(dev, "%s secs=%d, mins=%d, "
		"hours=%d, mday=%d, mon=%d, year=%d, wday=%d\n",
		"write", t->tm_sec, t->tm_min,
		t->tm_hour, t->tm_mday,
		t->tm_mon, t->tm_year, t->tm_wday);

	/* first register addr */
	buf[FM3130_RTC_SECONDS] = bin2bcd(t->tm_sec);
	buf[FM3130_RTC_MINUTES] = bin2bcd(t->tm_min);
	buf[FM3130_RTC_HOURS] = bin2bcd(t->tm_hour);
	buf[FM3130_RTC_DAY] = bin2bcd(t->tm_wday + 1);
	buf[FM3130_RTC_DATE] = bin2bcd(t->tm_mday);
	buf[FM3130_RTC_MONTHS] = bin2bcd(t->tm_mon + 1);

	/* assume 20YY not 19YY */
	tmp = t->tm_year - 100;
	buf[FM3130_RTC_YEARS] = bin2bcd(tmp);

	dev_dbg(dev, "%s: %15ph\n", "write", buf);

	fm3130_rtc_mode(dev, FM3130_MODE_WRITE);

	/* Writing time registers, we don't support multibyte transfers */
	for (i = 0; i < FM3130_CLOCK_REGS; i++) {
		i2c_smbus_write_byte_data(fm3130->client,
					FM3130_RTC_SECONDS + i,
					fm3130->regs[FM3130_RTC_SECONDS + i]);
	}

	fm3130_rtc_mode(dev, FM3130_MODE_NORMAL);

	/* We assume here that data are valid once written */
	if (!fm3130->data_valid)
		fm3130->data_valid = 1;
	return 0;
}