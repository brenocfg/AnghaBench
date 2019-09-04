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
struct pci_epf {TYPE_2__* driver; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {TYPE_1__* ops; int /*<<< orphan*/  owner; } ;
struct TYPE_3__ {int (* bind ) (struct pci_epf*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*) ; 
 int stub1 (struct pci_epf*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

int pci_epf_bind(struct pci_epf *epf)
{
	if (!epf->driver) {
		dev_WARN(&epf->dev, "epf device not bound to driver\n");
		return -EINVAL;
	}

	if (!try_module_get(epf->driver->owner))
		return -EAGAIN;

	return epf->driver->ops->bind(epf);
}