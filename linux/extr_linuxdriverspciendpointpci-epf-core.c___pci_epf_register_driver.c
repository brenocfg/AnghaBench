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
struct TYPE_4__ {struct module* owner; int /*<<< orphan*/ * bus; } ;
struct pci_epf_driver {TYPE_2__ driver; TYPE_1__* ops; } ;
struct module {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  linkup; int /*<<< orphan*/  unbind; int /*<<< orphan*/  bind; } ;

/* Variables and functions */
 int EINVAL ; 
 int driver_register (TYPE_2__*) ; 
 int /*<<< orphan*/  pci_epf_add_cfs (struct pci_epf_driver*) ; 
 int /*<<< orphan*/  pci_epf_bus_type ; 

int __pci_epf_register_driver(struct pci_epf_driver *driver,
			      struct module *owner)
{
	int ret;

	if (!driver->ops)
		return -EINVAL;

	if (!driver->ops->bind || !driver->ops->unbind || !driver->ops->linkup)
		return -EINVAL;

	driver->driver.bus = &pci_epf_bus_type;
	driver->driver.owner = owner;

	ret = driver_register(&driver->driver);
	if (ret)
		return ret;

	pci_epf_add_cfs(driver);

	return 0;
}