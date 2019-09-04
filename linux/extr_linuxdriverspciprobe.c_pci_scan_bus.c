#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_ops {int dummy; } ;
struct pci_bus {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  busn_resource ; 
 int /*<<< orphan*/  iomem_resource ; 
 int /*<<< orphan*/  ioport_resource ; 
 int /*<<< orphan*/  pci_add_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pci_bus* pci_create_root_bus (int /*<<< orphan*/ *,int,struct pci_ops*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_free_resource_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_scan_child_bus (struct pci_bus*) ; 
 int /*<<< orphan*/  resources ; 

struct pci_bus *pci_scan_bus(int bus, struct pci_ops *ops,
					void *sysdata)
{
	LIST_HEAD(resources);
	struct pci_bus *b;

	pci_add_resource(&resources, &ioport_resource);
	pci_add_resource(&resources, &iomem_resource);
	pci_add_resource(&resources, &busn_resource);
	b = pci_create_root_bus(NULL, bus, ops, sysdata, &resources);
	if (b) {
		pci_scan_child_bus(b);
	} else {
		pci_free_resource_list(&resources);
	}
	return b;
}