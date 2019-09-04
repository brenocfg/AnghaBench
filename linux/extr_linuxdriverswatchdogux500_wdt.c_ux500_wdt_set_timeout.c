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

/* Variables and functions */
 int /*<<< orphan*/  PRCMU_WDOG_ALL ; 
 int /*<<< orphan*/  prcmu_load_a9wdog (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  ux500_wdt_start (struct watchdog_device*) ; 
 int /*<<< orphan*/  ux500_wdt_stop (struct watchdog_device*) ; 

__attribute__((used)) static int ux500_wdt_set_timeout(struct watchdog_device *wdd,
				 unsigned int timeout)
{
	ux500_wdt_stop(wdd);
	prcmu_load_a9wdog(PRCMU_WDOG_ALL, timeout * 1000);
	ux500_wdt_start(wdd);

	return 0;
}