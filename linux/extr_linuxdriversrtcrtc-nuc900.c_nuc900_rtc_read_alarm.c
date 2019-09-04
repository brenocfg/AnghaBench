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
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_RTC_CAR ; 
 scalar_t__ REG_RTC_TAR ; 
 unsigned int __raw_readl (scalar_t__) ; 
 struct nuc900_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  nuc900_rtc_bcd2bin (unsigned int,unsigned int,int /*<<< orphan*/ *) ; 
 int rtc_valid_tm (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuc900_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct nuc900_rtc *rtc = dev_get_drvdata(dev);
	unsigned int timeval, carval;

	timeval = __raw_readl(rtc->rtc_reg + REG_RTC_TAR);
	carval	= __raw_readl(rtc->rtc_reg + REG_RTC_CAR);

	nuc900_rtc_bcd2bin(timeval, carval, &alrm->time);

	return rtc_valid_tm(&alrm->time);
}