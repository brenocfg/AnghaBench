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
typedef  int u32 ;
struct pcie_port {int /*<<< orphan*/  irq_domain; } ;
struct keystone_pcie {struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; struct pcie_port pp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ MSI0_IRQ_STATUS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int,int,int) ; 
 int /*<<< orphan*/  generic_handle_irq (int) ; 
 int irq_linear_revmap (int /*<<< orphan*/ ,int) ; 
 int ks_dw_app_readl (struct keystone_pcie*,scalar_t__) ; 

void ks_dw_pcie_handle_msi_irq(struct keystone_pcie *ks_pcie, int offset)
{
	struct dw_pcie *pci = ks_pcie->pci;
	struct pcie_port *pp = &pci->pp;
	struct device *dev = pci->dev;
	u32 pending, vector;
	int src, virq;

	pending = ks_dw_app_readl(ks_pcie, MSI0_IRQ_STATUS + (offset << 4));

	/*
	 * MSI0 status bit 0-3 shows vectors 0, 8, 16, 24, MSI1 status bit
	 * shows 1, 9, 17, 25 and so forth
	 */
	for (src = 0; src < 4; src++) {
		if (BIT(src) & pending) {
			vector = offset + (src << 3);
			virq = irq_linear_revmap(pp->irq_domain, vector);
			dev_dbg(dev, "irq: bit %d, vector %d, virq %d\n",
				src, vector, virq);
			generic_handle_irq(virq);
		}
	}
}