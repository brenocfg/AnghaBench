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
typedef  unsigned int uint32_t ;
struct watchdog_device {int dummy; } ;
struct dc_wdt {int /*<<< orphan*/  clk; scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ TIMER_A_COUNT ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 unsigned int readl_relaxed (scalar_t__) ; 
 struct dc_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 

__attribute__((used)) static unsigned int dc_wdt_get_timeleft(struct watchdog_device *wdog)
{
	struct dc_wdt *wdt = watchdog_get_drvdata(wdog);
	uint32_t count = readl_relaxed(wdt->base + TIMER_A_COUNT);

	return count / clk_get_rate(wdt->clk);
}