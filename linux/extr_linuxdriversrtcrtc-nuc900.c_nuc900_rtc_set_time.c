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
struct nuc900_rtc {scalar_t__ rtc_reg; } ;
struct nuc900_bcd_time {unsigned long bcd_mday; unsigned long bcd_mon; unsigned long bcd_year; unsigned long bcd_sec; unsigned long bcd_min; unsigned long bcd_hour; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int*) ; 
 int PTR_ERR (int*) ; 
 scalar_t__ REG_RTC_CLR ; 
 scalar_t__ REG_RTC_TLR ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,scalar_t__) ; 
 int* check_rtc_access_enable (struct nuc900_rtc*) ; 
 struct nuc900_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  nuc900_rtc_bin2bcd (struct device*,struct rtc_time*,struct nuc900_bcd_time*) ; 

__attribute__((used)) static int nuc900_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct nuc900_rtc *rtc = dev_get_drvdata(dev);
	struct nuc900_bcd_time gettm;
	unsigned long val;
	int *err;

	nuc900_rtc_bin2bcd(dev, tm, &gettm);

	err = check_rtc_access_enable(rtc);
	if (IS_ERR(err))
		return PTR_ERR(err);

	val = gettm.bcd_mday | gettm.bcd_mon | gettm.bcd_year;
	__raw_writel(val, rtc->rtc_reg + REG_RTC_CLR);

	val = gettm.bcd_sec | gettm.bcd_min | gettm.bcd_hour;
	__raw_writel(val, rtc->rtc_reg + REG_RTC_TLR);

	return 0;
}