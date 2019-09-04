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
struct ts4800_wdt {int /*<<< orphan*/  wdd; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct ts4800_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ts4800_wdt_remove(struct platform_device *pdev)
{
	struct ts4800_wdt *wdt = platform_get_drvdata(pdev);

	watchdog_unregister_device(&wdt->wdd);

	return 0;
}