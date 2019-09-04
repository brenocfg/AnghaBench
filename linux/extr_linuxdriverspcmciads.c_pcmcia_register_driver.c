#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; int /*<<< orphan*/  owner; int /*<<< orphan*/ * bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;
struct pcmcia_driver {TYPE_2__ drv; int /*<<< orphan*/  name; TYPE_1__ dynids; int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int driver_register (TYPE_2__*) ; 
 int /*<<< orphan*/  driver_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcmcia_bus_type ; 
 int /*<<< orphan*/  pcmcia_check_driver (struct pcmcia_driver*) ; 
 int pcmcia_create_newid_file (struct pcmcia_driver*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

int pcmcia_register_driver(struct pcmcia_driver *driver)
{
	int error;

	if (!driver)
		return -EINVAL;

	pcmcia_check_driver(driver);

	/* initialize common fields */
	driver->drv.bus = &pcmcia_bus_type;
	driver->drv.owner = driver->owner;
	driver->drv.name = driver->name;
	mutex_init(&driver->dynids.lock);
	INIT_LIST_HEAD(&driver->dynids.list);

	pr_debug("registering driver %s\n", driver->name);

	error = driver_register(&driver->drv);
	if (error < 0)
		return error;

	error = pcmcia_create_newid_file(driver);
	if (error)
		driver_unregister(&driver->drv);

	return error;
}