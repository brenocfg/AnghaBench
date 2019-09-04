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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/ * parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  at91rm9200_restart_nb ; 
 TYPE_1__ at91wdt_miscdev ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  misc_deregister (TYPE_1__*) ; 
 int unregister_restart_handler (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int at91wdt_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	int res;

	res = unregister_restart_handler(&at91rm9200_restart_nb);
	if (res)
		dev_warn(dev, "failed to unregister restart handler\n");

	misc_deregister(&at91wdt_miscdev);
	at91wdt_miscdev.parent = NULL;

	return res;
}