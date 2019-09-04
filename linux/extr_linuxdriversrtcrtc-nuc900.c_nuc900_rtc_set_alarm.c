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
struct rtc_wkalrm {int /*<<< orphan*/  time; } ;
struct nuc900_rtc {scalar_t__ rtc_reg; } ;
struct nuc900_bcd_time {unsigned long bcd_mday; unsigned long bcd_mon; unsigned long bcd_year; unsigned long bcd_sec; unsigned long bcd_min; unsigned long bcd_hour; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int*) ; 
 int PTR_ERR (int*) ; 
 scalar_t__ REG_RTC_CAR ; 
 scalar_t__ REG_RTC_TAR ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int* check_rtc_access_enable (struct nuc900_rtc*) ; 
 struct nuc900_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  nuc900_rtc_bin2bcd (struct device*,int /*<<< orphan*/ *,struct nuc900_bcd_time*) ; 

__attribute__((used)) static int nuc900_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct nuc900_rtc *rtc = dev_get_drvdata(dev);
	struct nuc900_bcd_time tm;
	unsigned long val;
	int *err;

	nuc900_rtc_bin2bcd(dev, &alrm->time, &tm);

	err = check_rtc_access_enable(rtc);
	if (IS_ERR(err))
		return PTR_ERR(err);

	val = tm.bcd_mday | tm.bcd_mon | tm.bcd_year;
	__raw_writel(val, rtc->rtc_reg + REG_RTC_CAR);

	val = tm.bcd_sec | tm.bcd_min | tm.bcd_hour;
	__raw_writel(val, rtc->rtc_reg + REG_RTC_TAR);

	return 0;
}