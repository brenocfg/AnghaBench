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
struct pci_bus {int /*<<< orphan*/  dev; } ;
struct irq_domain {int dummy; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DOMAIN_BUS_PCI_MSI ; 
 struct irq_domain* irq_find_matching_fwnode (struct fwnode_handle*,int /*<<< orphan*/ ) ; 
 struct fwnode_handle* pci_msi_get_fwnode_cb (int /*<<< orphan*/ *) ; 

struct irq_domain *pci_host_bridge_acpi_msi_domain(struct pci_bus *bus)
{
	struct fwnode_handle *fwnode;

	if (!pci_msi_get_fwnode_cb)
		return NULL;

	fwnode = pci_msi_get_fwnode_cb(&bus->dev);
	if (!fwnode)
		return NULL;

	return irq_find_matching_fwnode(fwnode, DOMAIN_BUS_PCI_MSI);
}