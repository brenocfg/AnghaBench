#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct watchdog_device {TYPE_2__* wd_data; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__ cdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  watchdog_cdev_unregister (struct watchdog_device*) ; 
 int /*<<< orphan*/  watchdog_class ; 
 int /*<<< orphan*/  watchdog_unregister_pretimeout (struct watchdog_device*) ; 

void watchdog_dev_unregister(struct watchdog_device *wdd)
{
	watchdog_unregister_pretimeout(wdd);
	device_destroy(&watchdog_class, wdd->wd_data->cdev.dev);
	watchdog_cdev_unregister(wdd);
}