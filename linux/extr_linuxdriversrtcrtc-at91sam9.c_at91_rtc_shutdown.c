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
struct sam9_rtc {int imr; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int AT91_RTT_ALMIEN ; 
 int AT91_RTT_RTTINCIEN ; 
 int /*<<< orphan*/  MR ; 
 struct sam9_rtc* platform_get_drvdata (struct platform_device*) ; 
 int rtt_readl (struct sam9_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtt_writel (struct sam9_rtc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void at91_rtc_shutdown(struct platform_device *pdev)
{
	struct sam9_rtc	*rtc = platform_get_drvdata(pdev);
	u32		mr = rtt_readl(rtc, MR);

	rtc->imr = mr & (AT91_RTT_ALMIEN | AT91_RTT_RTTINCIEN);
	rtt_writel(rtc, MR, mr & ~rtc->imr);
}