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
struct mtk_pcie_port {int /*<<< orphan*/  inner_domain; TYPE_1__* pcie; int /*<<< orphan*/  msi_domain; int /*<<< orphan*/  lock; } ;
struct fwnode_handle {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_3__ {TYPE_2__* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTK_MSI_IRQS_NUM ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  irq_domain_create_linear (struct fwnode_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct mtk_pcie_port*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msi_domain_ops ; 
 int /*<<< orphan*/  mtk_msi_domain_info ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct fwnode_handle* of_node_to_fwnode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_msi_create_irq_domain (struct fwnode_handle*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mtk_pcie_allocate_msi_domains(struct mtk_pcie_port *port)
{
	struct fwnode_handle *fwnode = of_node_to_fwnode(port->pcie->dev->of_node);

	mutex_init(&port->lock);

	port->inner_domain = irq_domain_create_linear(fwnode, MTK_MSI_IRQS_NUM,
						      &msi_domain_ops, port);
	if (!port->inner_domain) {
		dev_err(port->pcie->dev, "failed to create IRQ domain\n");
		return -ENOMEM;
	}

	port->msi_domain = pci_msi_create_irq_domain(fwnode, &mtk_msi_domain_info,
						     port->inner_domain);
	if (!port->msi_domain) {
		dev_err(port->pcie->dev, "failed to create MSI domain\n");
		irq_domain_remove(port->inner_domain);
		return -ENOMEM;
	}

	return 0;
}