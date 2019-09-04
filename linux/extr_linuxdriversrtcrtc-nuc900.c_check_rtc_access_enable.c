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
struct nuc900_rtc {scalar_t__ rtc_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AERPOWERON ; 
 int AERRWENB ; 
 int /*<<< orphan*/  EPERM ; 
 int* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIRRESET ; 
 scalar_t__ REG_RTC_AER ; 
 scalar_t__ REG_RTC_INIR ; 
 int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int *check_rtc_access_enable(struct nuc900_rtc *nuc900_rtc)
{
	unsigned int timeout = 0x1000;
	__raw_writel(INIRRESET, nuc900_rtc->rtc_reg + REG_RTC_INIR);

	mdelay(10);

	__raw_writel(AERPOWERON, nuc900_rtc->rtc_reg + REG_RTC_AER);

	while (!(__raw_readl(nuc900_rtc->rtc_reg + REG_RTC_AER) & AERRWENB)
								&& --timeout)
		mdelay(1);

	if (!timeout)
		return ERR_PTR(-EPERM);

	return NULL;
}