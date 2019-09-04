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
struct msi_domain_info {int flags; struct irq_chip* chip; } ;
struct irq_chip {char* name; int /*<<< orphan*/  irq_set_affinity; int /*<<< orphan*/  irq_compose_msi_msg; } ;
struct device_node {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct advk_pcie {int /*<<< orphan*/  msi_inner_domain; int /*<<< orphan*/  msi_domain; int /*<<< orphan*/  msi_msg; struct msi_domain_info msi_domain_info; struct irq_chip msi_irq_chip; struct irq_chip msi_bottom_irq_chip; int /*<<< orphan*/  msi_used_lock; TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int MSI_FLAG_MULTI_PCI_MSI ; 
 int MSI_FLAG_USE_DEF_CHIP_OPS ; 
 int MSI_FLAG_USE_DEF_DOM_OPS ; 
 int /*<<< orphan*/  MSI_IRQ_NUM ; 
 int /*<<< orphan*/  PCIE_MSI_ADDR_HIGH_REG ; 
 int /*<<< orphan*/  PCIE_MSI_ADDR_LOW_REG ; 
 int /*<<< orphan*/  advk_msi_domain_ops ; 
 int /*<<< orphan*/  advk_msi_irq_compose_msi_msg ; 
 int /*<<< orphan*/  advk_msi_set_affinity ; 
 int /*<<< orphan*/  advk_writel (struct advk_pcie*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_domain_add_linear (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct advk_pcie*) ; 
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_to_fwnode (struct device_node*) ; 
 int /*<<< orphan*/  pci_msi_create_irq_domain (int /*<<< orphan*/ ,struct msi_domain_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int advk_pcie_init_msi_irq_domain(struct advk_pcie *pcie)
{
	struct device *dev = &pcie->pdev->dev;
	struct device_node *node = dev->of_node;
	struct irq_chip *bottom_ic, *msi_ic;
	struct msi_domain_info *msi_di;
	phys_addr_t msi_msg_phys;

	mutex_init(&pcie->msi_used_lock);

	bottom_ic = &pcie->msi_bottom_irq_chip;

	bottom_ic->name = "MSI";
	bottom_ic->irq_compose_msi_msg = advk_msi_irq_compose_msi_msg;
	bottom_ic->irq_set_affinity = advk_msi_set_affinity;

	msi_ic = &pcie->msi_irq_chip;
	msi_ic->name = "advk-MSI";

	msi_di = &pcie->msi_domain_info;
	msi_di->flags = MSI_FLAG_USE_DEF_DOM_OPS | MSI_FLAG_USE_DEF_CHIP_OPS |
		MSI_FLAG_MULTI_PCI_MSI;
	msi_di->chip = msi_ic;

	msi_msg_phys = virt_to_phys(&pcie->msi_msg);

	advk_writel(pcie, lower_32_bits(msi_msg_phys),
		    PCIE_MSI_ADDR_LOW_REG);
	advk_writel(pcie, upper_32_bits(msi_msg_phys),
		    PCIE_MSI_ADDR_HIGH_REG);

	pcie->msi_inner_domain =
		irq_domain_add_linear(NULL, MSI_IRQ_NUM,
				      &advk_msi_domain_ops, pcie);
	if (!pcie->msi_inner_domain)
		return -ENOMEM;

	pcie->msi_domain =
		pci_msi_create_irq_domain(of_node_to_fwnode(node),
					  msi_di, pcie->msi_inner_domain);
	if (!pcie->msi_domain) {
		irq_domain_remove(pcie->msi_inner_domain);
		return -ENOMEM;
	}

	return 0;
}