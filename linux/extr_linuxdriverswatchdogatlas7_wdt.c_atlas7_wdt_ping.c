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
struct atlas7_wdog {int tick_rate; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ ATLAS7_WDT_CNT ; 
 scalar_t__ ATLAS7_WDT_CNT_MATCH ; 
 int readl (scalar_t__) ; 
 struct atlas7_wdog* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int atlas7_wdt_ping(struct watchdog_device *wdd)
{
	struct atlas7_wdog *wdt = watchdog_get_drvdata(wdd);
	u32 counter, match, delta;

	counter = readl(wdt->base + ATLAS7_WDT_CNT);
	delta = wdd->timeout * wdt->tick_rate;
	match = counter + delta;

	writel(match, wdt->base + ATLAS7_WDT_CNT_MATCH);

	return 0;
}