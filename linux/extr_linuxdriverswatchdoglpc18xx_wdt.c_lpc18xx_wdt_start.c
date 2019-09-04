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
struct lpc18xx_wdt_dev {scalar_t__ base; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 scalar_t__ LPC18XX_WDT_MOD ; 
 unsigned int LPC18XX_WDT_MOD_WDEN ; 
 unsigned int LPC18XX_WDT_MOD_WDRESET ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpc18xx_wdt_feed (struct watchdog_device*) ; 
 unsigned int readl (scalar_t__) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 struct lpc18xx_wdt_dev* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static int lpc18xx_wdt_start(struct watchdog_device *wdt_dev)
{
	struct lpc18xx_wdt_dev *lpc18xx_wdt = watchdog_get_drvdata(wdt_dev);
	unsigned int val;

	if (timer_pending(&lpc18xx_wdt->timer))
		del_timer(&lpc18xx_wdt->timer);

	val = readl(lpc18xx_wdt->base + LPC18XX_WDT_MOD);
	val |= LPC18XX_WDT_MOD_WDEN;
	val |= LPC18XX_WDT_MOD_WDRESET;
	writel(val, lpc18xx_wdt->base + LPC18XX_WDT_MOD);

	/*
	 * Setting the WDEN bit in the WDMOD register is not sufficient to
	 * enable the Watchdog. A valid feed sequence must be completed after
	 * setting WDEN before the Watchdog is capable of generating a reset.
	 */
	lpc18xx_wdt_feed(wdt_dev);

	return 0;
}