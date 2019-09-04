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
struct tegra_msi {int /*<<< orphan*/  used; int /*<<< orphan*/  domain; } ;
struct tegra_pcie {struct tegra_msi msi; struct device* dev; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 scalar_t__ AFI_MSI_VEC0 ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 unsigned long afi_readl (struct tegra_pcie*,scalar_t__) ; 
 int /*<<< orphan*/  afi_writel (struct tegra_pcie*,int,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 unsigned int find_first_bit (unsigned long*,int) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 unsigned int irq_find_mapping (int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t tegra_pcie_msi_irq(int irq, void *data)
{
	struct tegra_pcie *pcie = data;
	struct device *dev = pcie->dev;
	struct tegra_msi *msi = &pcie->msi;
	unsigned int i, processed = 0;

	for (i = 0; i < 8; i++) {
		unsigned long reg = afi_readl(pcie, AFI_MSI_VEC0 + i * 4);

		while (reg) {
			unsigned int offset = find_first_bit(&reg, 32);
			unsigned int index = i * 32 + offset;
			unsigned int irq;

			/* clear the interrupt */
			afi_writel(pcie, 1 << offset, AFI_MSI_VEC0 + i * 4);

			irq = irq_find_mapping(msi->domain, index);
			if (irq) {
				if (test_bit(index, msi->used))
					generic_handle_irq(irq);
				else
					dev_info(dev, "unhandled MSI\n");
			} else {
				/*
				 * that's weird who triggered this?
				 * just clear it
				 */
				dev_info(dev, "unexpected MSI\n");
			}

			/* see if there's any more pending in this vector */
			reg = afi_readl(pcie, AFI_MSI_VEC0 + i * 4);

			processed++;
		}
	}

	return processed > 0 ? IRQ_HANDLED : IRQ_NONE;
}