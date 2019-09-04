#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_driver {int dummy; } ;
struct xenbus_driver {struct device_driver driver; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_for_each_dev (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct device_driver*,int /*<<< orphan*/ ) ; 
 scalar_t__ exists_essential_connecting_device (struct device_driver*) ; 
 scalar_t__ exists_non_essential_connecting_device (struct device_driver*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  print_device_status ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  ready_to_wait_for_devices ; 
 scalar_t__ wait_loop (unsigned long,int,unsigned int*) ; 
 int /*<<< orphan*/  xen_domain () ; 
 TYPE_1__ xenbus_frontend ; 

__attribute__((used)) static void wait_for_devices(struct xenbus_driver *xendrv)
{
	unsigned long start = jiffies;
	struct device_driver *drv = xendrv ? &xendrv->driver : NULL;
	unsigned int seconds_waited = 0;

	if (!ready_to_wait_for_devices || !xen_domain())
		return;

	while (exists_non_essential_connecting_device(drv))
		if (wait_loop(start, 30, &seconds_waited))
			break;

	/* Skips PVKB and PVFB check.*/
	while (exists_essential_connecting_device(drv))
		if (wait_loop(start, 270, &seconds_waited))
			break;

	if (seconds_waited)
		printk("\n");

	bus_for_each_dev(&xenbus_frontend.bus, NULL, drv,
			 print_device_status);
}