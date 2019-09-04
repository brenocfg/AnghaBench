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
typedef  int u32 ;
struct rtc_wkalrm {int enabled; int pending; int /*<<< orphan*/  time; } ;
struct pxa_rtc {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDAR1 ; 
 int /*<<< orphan*/  RTSR ; 
 int RTSR_RDAL1 ; 
 int RTSR_RDALE1 ; 
 int /*<<< orphan*/  RYAR1 ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int rtc_readl (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tm_calc (int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pxa_rtc_read_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);
	u32 rtsr, ryar, rdar;

	ryar = rtc_readl(pxa_rtc, RYAR1);
	rdar = rtc_readl(pxa_rtc, RDAR1);
	tm_calc(ryar, rdar, &alrm->time);

	rtsr = rtc_readl(pxa_rtc, RTSR);
	alrm->enabled = (rtsr & RTSR_RDALE1) ? 1 : 0;
	alrm->pending = (rtsr & RTSR_RDAL1) ? 1 : 0;
	return 0;
}