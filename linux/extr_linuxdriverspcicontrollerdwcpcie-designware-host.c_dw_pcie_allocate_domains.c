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
struct pcie_port {int /*<<< orphan*/  irq_domain; int /*<<< orphan*/  msi_domain; int /*<<< orphan*/  num_vectors; } ;
struct fwnode_handle {int dummy; } ;
struct dw_pcie {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dw_pcie_msi_domain_info ; 
 int /*<<< orphan*/  dw_pcie_msi_domain_ops ; 
 int /*<<< orphan*/  irq_domain_create_linear (struct fwnode_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct pcie_port*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 struct fwnode_handle* of_node_to_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_msi_create_irq_domain (struct fwnode_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct dw_pcie* to_dw_pcie_from_pp (struct pcie_port*) ; 

int dw_pcie_allocate_domains(struct pcie_port *pp)
{
	struct dw_pcie *pci = to_dw_pcie_from_pp(pp);
	struct fwnode_handle *fwnode = of_node_to_fwnode(pci->dev->of_node);

	pp->irq_domain = irq_domain_create_linear(fwnode, pp->num_vectors,
					       &dw_pcie_msi_domain_ops, pp);
	if (!pp->irq_domain) {
		dev_err(pci->dev, "Failed to create IRQ domain\n");
		return -ENOMEM;
	}

	pp->msi_domain = pci_msi_create_irq_domain(fwnode,
						   &dw_pcie_msi_domain_info,
						   pp->irq_domain);
	if (!pp->msi_domain) {
		dev_err(pci->dev, "Failed to create MSI domain\n");
		irq_domain_remove(pp->irq_domain);
		return -ENOMEM;
	}

	return 0;
}