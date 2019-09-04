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

/* Variables and functions */
 struct watchdog_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sirfsoc_wdt_disable (struct watchdog_device*) ; 

__attribute__((used)) static void sirfsoc_wdt_shutdown(struct platform_device *pdev)
{
	struct watchdog_device *wdd = platform_get_drvdata(pdev);

	sirfsoc_wdt_disable(wdd);
}