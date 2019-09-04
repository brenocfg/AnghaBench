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
struct TYPE_3__ {int /*<<< orphan*/ * bus; int /*<<< orphan*/  name; } ;
struct vme_driver {TYPE_1__ driver; int /*<<< orphan*/  devices; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int __vme_register_driver (struct vme_driver*,unsigned int) ; 
 int driver_register (TYPE_1__*) ; 
 int /*<<< orphan*/  driver_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  vme_bus_type ; 

int vme_register_driver(struct vme_driver *drv, unsigned int ndevs)
{
	int err;

	drv->driver.name = drv->name;
	drv->driver.bus = &vme_bus_type;
	INIT_LIST_HEAD(&drv->devices);

	err = driver_register(&drv->driver);
	if (err)
		return err;

	err = __vme_register_driver(drv, ndevs);
	if (err)
		driver_unregister(&drv->driver);

	return err;
}