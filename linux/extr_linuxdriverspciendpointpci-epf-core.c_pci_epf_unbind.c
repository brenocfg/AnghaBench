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
struct TYPE_4__ {int /*<<< orphan*/  owner; TYPE_1__* ops; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* unbind ) (struct pci_epf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct pci_epf*) ; 

void pci_epf_unbind(struct pci_epf *epf)
{
	if (!epf->driver) {
		dev_WARN(&epf->dev, "epf device not bound to driver\n");
		return;
	}

	epf->driver->ops->unbind(epf);
	module_put(epf->driver->owner);
}