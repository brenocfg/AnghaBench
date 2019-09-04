#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_1__ ks8695wdt_miscdev ; 
 int misc_register (TYPE_1__*) ; 
 scalar_t__ nowayout ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wdt_time ; 

__attribute__((used)) static int ks8695wdt_probe(struct platform_device *pdev)
{
	int res;

	if (ks8695wdt_miscdev.parent)
		return -EBUSY;
	ks8695wdt_miscdev.parent = &pdev->dev;

	res = misc_register(&ks8695wdt_miscdev);
	if (res)
		return res;

	pr_info("KS8695 Watchdog Timer enabled (%d seconds%s)\n",
		wdt_time, nowayout ? ", nowayout" : "");
	return 0;
}