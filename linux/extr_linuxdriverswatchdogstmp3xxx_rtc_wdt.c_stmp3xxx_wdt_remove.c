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

/* Variables and functions */
 int /*<<< orphan*/  stmp3xxx_wdd ; 
 int /*<<< orphan*/  unregister_reboot_notifier (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdt_notifier ; 

__attribute__((used)) static int stmp3xxx_wdt_remove(struct platform_device *pdev)
{
	unregister_reboot_notifier(&wdt_notifier);
	watchdog_unregister_device(&stmp3xxx_wdd);
	return 0;
}