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
struct pxa_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDCR ; 
 int /*<<< orphan*/  RYCR ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  rdxr_calc (struct rtc_time*) ; 
 int /*<<< orphan*/  rtc_writel (struct pxa_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ryxr_calc (struct rtc_time*) ; 

__attribute__((used)) static int pxa_rtc_set_time(struct device *dev, struct rtc_time *tm)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	rtc_writel(pxa_rtc, RYCR, ryxr_calc(tm));
	rtc_writel(pxa_rtc, RDCR, rdxr_calc(tm));

	return 0;
}