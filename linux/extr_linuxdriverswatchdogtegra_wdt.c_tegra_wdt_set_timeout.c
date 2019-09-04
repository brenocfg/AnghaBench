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

/* Variables and functions */
 int tegra_wdt_start (struct watchdog_device*) ; 
 int /*<<< orphan*/  tegra_wdt_stop (struct watchdog_device*) ; 
 scalar_t__ watchdog_active (struct watchdog_device*) ; 

__attribute__((used)) static int tegra_wdt_set_timeout(struct watchdog_device *wdd,
				 unsigned int timeout)
{
	wdd->timeout = timeout;

	if (watchdog_active(wdd)) {
		tegra_wdt_stop(wdd);
		return tegra_wdt_start(wdd);
	}

	return 0;
}