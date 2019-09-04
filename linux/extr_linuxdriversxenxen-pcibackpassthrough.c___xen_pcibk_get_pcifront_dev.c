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
struct xen_pcibk_device {int dummy; } ;
struct pci_dev {unsigned int devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {unsigned int number; } ;

/* Variables and functions */
 unsigned int pci_domain_nr (TYPE_1__*) ; 

__attribute__((used)) static int __xen_pcibk_get_pcifront_dev(struct pci_dev *pcidev,
					struct xen_pcibk_device *pdev,
					unsigned int *domain, unsigned int *bus,
					unsigned int *devfn)
{
	*domain = pci_domain_nr(pcidev->bus);
	*bus = pcidev->bus->number;
	*devfn = pcidev->devfn;
	return 1;
}