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
struct aspeed_wdt {scalar_t__ base; int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 scalar_t__ WDT_CTRL ; 
 int /*<<< orphan*/  WDT_CTRL_ENABLE ; 
 struct aspeed_wdt* to_aspeed_wdt (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int aspeed_wdt_stop(struct watchdog_device *wdd)
{
	struct aspeed_wdt *wdt = to_aspeed_wdt(wdd);

	wdt->ctrl &= ~WDT_CTRL_ENABLE;
	writel(wdt->ctrl, wdt->base + WDT_CTRL);

	return 0;
}