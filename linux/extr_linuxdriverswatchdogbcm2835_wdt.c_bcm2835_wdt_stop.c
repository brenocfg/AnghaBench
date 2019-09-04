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
struct watchdog_device {int dummy; } ;
struct bcm2835_wdt {scalar_t__ base; } ;

/* Variables and functions */
 int PM_PASSWORD ; 
 scalar_t__ PM_RSTC ; 
 int PM_RSTC_RESET ; 
 struct bcm2835_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int bcm2835_wdt_stop(struct watchdog_device *wdog)
{
	struct bcm2835_wdt *wdt = watchdog_get_drvdata(wdog);

	writel_relaxed(PM_PASSWORD | PM_RSTC_RESET, wdt->base + PM_RSTC);
	return 0;
}