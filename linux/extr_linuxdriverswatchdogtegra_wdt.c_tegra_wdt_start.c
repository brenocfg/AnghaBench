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
struct watchdog_device {int timeout; } ;
struct tegra_wdt {scalar_t__ wdt_regs; scalar_t__ tmr_regs; } ;

/* Variables and functions */
 int TIMER_EN ; 
 int TIMER_PERIODIC ; 
 scalar_t__ TIMER_PTV ; 
 scalar_t__ WDT_CFG ; 
 int WDT_CFG_PERIOD_SHIFT ; 
 int WDT_CFG_PMC2CAR_RST_EN ; 
 scalar_t__ WDT_CMD ; 
 int WDT_CMD_START_COUNTER ; 
 int WDT_TIMER_ID ; 
 struct tegra_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int tegra_wdt_start(struct watchdog_device *wdd)
{
	struct tegra_wdt *wdt = watchdog_get_drvdata(wdd);
	u32 val;

	/*
	 * This thing has a fixed 1MHz clock.  Normally, we would set the
	 * period to 1 second by writing 1000000ul, but the watchdog system
	 * reset actually occurs on the 4th expiration of this counter,
	 * so we set the period to 1/4 of this amount.
	 */
	val = 1000000ul / 4;
	val |= (TIMER_EN | TIMER_PERIODIC);
	writel(val, wdt->tmr_regs + TIMER_PTV);

	/*
	 * Set number of periods and start counter.
	 *
	 * Interrupt handler is not required for user space
	 * WDT accesses, since the caller is responsible to ping the
	 * WDT to reset the counter before expiration, through ioctls.
	 */
	val = WDT_TIMER_ID |
	      (wdd->timeout << WDT_CFG_PERIOD_SHIFT) |
	      WDT_CFG_PMC2CAR_RST_EN;
	writel(val, wdt->wdt_regs + WDT_CFG);

	writel(WDT_CMD_START_COUNTER, wdt->wdt_regs + WDT_CMD);

	return 0;
}