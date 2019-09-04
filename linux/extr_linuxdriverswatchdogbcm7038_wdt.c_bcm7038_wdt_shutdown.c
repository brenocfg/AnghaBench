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
struct platform_device {int dummy; } ;
struct bcm7038_watchdog {int /*<<< orphan*/  wdd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcm7038_wdt_stop (int /*<<< orphan*/ *) ; 
 struct bcm7038_watchdog* platform_get_drvdata (struct platform_device*) ; 
 scalar_t__ watchdog_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bcm7038_wdt_shutdown(struct platform_device *pdev)
{
	struct bcm7038_watchdog *wdt = platform_get_drvdata(pdev);

	if (watchdog_active(&wdt->wdd))
		bcm7038_wdt_stop(&wdt->wdd);
}