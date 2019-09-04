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
struct watchdog_device {unsigned int timeout; } ;
struct dc_wdt {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dc_wdt_set (struct dc_wdt*,unsigned int) ; 
 struct dc_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static int dc_wdt_set_timeout(struct watchdog_device *wdog, unsigned int t)
{
	struct dc_wdt *wdt = watchdog_get_drvdata(wdog);

	dc_wdt_set(wdt, t * clk_get_rate(wdt->clk));
	wdog->timeout = t;

	return 0;
}