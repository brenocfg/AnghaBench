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
struct pcistub_device_id {scalar_t__ domain; scalar_t__ bus; scalar_t__ devfn; } ;
struct pci_dev {scalar_t__ devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {scalar_t__ number; struct pci_dev* self; } ;

/* Variables and functions */
 scalar_t__ pci_domain_nr (TYPE_1__*) ; 

__attribute__((used)) static int pcistub_match_one(struct pci_dev *dev,
			     struct pcistub_device_id *pdev_id)
{
	/* Match the specified device by domain, bus, slot, func and also if
	 * any of the device's parent bridges match.
	 */
	for (; dev != NULL; dev = dev->bus->self) {
		if (pci_domain_nr(dev->bus) == pdev_id->domain
		    && dev->bus->number == pdev_id->bus
		    && dev->devfn == pdev_id->devfn)
			return 1;

		/* Sometimes topmost bridge links to itself. */
		if (dev == dev->bus->self)
			break;
	}

	return 0;
}