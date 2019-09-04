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
struct aspeed_wdt {int ctrl; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ WDT_CTRL ; 
 int WDT_CTRL_ENABLE ; 
 scalar_t__ WDT_RELOAD_VALUE ; 
 scalar_t__ WDT_RESTART ; 
 int WDT_RESTART_MAGIC ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void aspeed_wdt_enable(struct aspeed_wdt *wdt, int count)
{
	wdt->ctrl |= WDT_CTRL_ENABLE;

	writel(0, wdt->base + WDT_CTRL);
	writel(count, wdt->base + WDT_RELOAD_VALUE);
	writel(WDT_RESTART_MAGIC, wdt->base + WDT_RESTART);
	writel(wdt->ctrl, wdt->base + WDT_CTRL);
}