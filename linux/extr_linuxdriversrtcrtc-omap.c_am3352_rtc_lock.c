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
struct omap_rtc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_RTC_KICK0_REG ; 
 int /*<<< orphan*/  OMAP_RTC_KICK1_REG ; 
 int /*<<< orphan*/  rtc_writel (struct omap_rtc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void am3352_rtc_lock(struct omap_rtc *rtc)
{
	rtc_writel(rtc, OMAP_RTC_KICK0_REG, 0);
	rtc_writel(rtc, OMAP_RTC_KICK1_REG, 0);
}