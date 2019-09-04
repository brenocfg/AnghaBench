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
struct platform_device {int dummy; } ;
struct kempld_wdt_data {struct watchdog_device wdd; } ;

/* Variables and functions */
 int kempld_wdt_stop (struct watchdog_device*) ; 
 int /*<<< orphan*/  nowayout ; 
 struct kempld_wdt_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  watchdog_unregister_device (struct watchdog_device*) ; 

__attribute__((used)) static int kempld_wdt_remove(struct platform_device *pdev)
{
	struct kempld_wdt_data *wdt_data = platform_get_drvdata(pdev);
	struct watchdog_device *wdd = &wdt_data->wdd;
	int ret = 0;

	if (!nowayout)
		ret = kempld_wdt_stop(wdd);
	watchdog_unregister_device(wdd);

	return ret;
}