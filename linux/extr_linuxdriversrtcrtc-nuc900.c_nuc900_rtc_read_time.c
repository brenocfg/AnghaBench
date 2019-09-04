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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_RTC_CLR ; 
 scalar_t__ REG_RTC_TLR ; 
 unsigned int __raw_readl (scalar_t__) ; 
 struct nuc900_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  nuc900_rtc_bcd2bin (unsigned int,unsigned int,struct rtc_time*) ; 

__attribute__((used)) static int nuc900_rtc_read_time(struct device *dev, struct rtc_time *tm)
{
	struct nuc900_rtc *rtc = dev_get_drvdata(dev);
	unsigned int timeval, clrval;

	timeval = __raw_readl(rtc->rtc_reg + REG_RTC_TLR);
	clrval	= __raw_readl(rtc->rtc_reg + REG_RTC_CLR);

	nuc900_rtc_bcd2bin(timeval, clrval, tm);

	return 0;
}