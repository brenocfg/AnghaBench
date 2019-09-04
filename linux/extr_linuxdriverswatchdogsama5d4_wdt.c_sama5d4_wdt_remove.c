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
struct sama5d4_wdt {int /*<<< orphan*/  wdd; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct sama5d4_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sama5d4_wdt_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sama5d4_wdt_remove(struct platform_device *pdev)
{
	struct sama5d4_wdt *wdt = platform_get_drvdata(pdev);

	sama5d4_wdt_stop(&wdt->wdd);

	watchdog_unregister_device(&wdt->wdd);

	return 0;
}