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
struct tegra_pcie_soc {scalar_t__ program_uphy; } ;
struct resource {scalar_t__ start; scalar_t__ end; } ;
struct tegra_pcie {int irq; void* cfg; struct resource cs; void* afi; void* pads; struct tegra_pcie_soc* soc; struct device* dev; } ;
struct platform_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ SZ_4K ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 void* devm_ioremap_resource (struct device*,struct resource*) ; 
 int platform_get_irq_byname (struct platform_device*,char*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct tegra_pcie*) ; 
 int tegra_pcie_clocks_get (struct tegra_pcie*) ; 
 int /*<<< orphan*/  tegra_pcie_isr ; 
 int tegra_pcie_phys_get (struct tegra_pcie*) ; 
 int /*<<< orphan*/  tegra_pcie_phys_put (struct tegra_pcie*) ; 
 int tegra_pcie_resets_get (struct tegra_pcie*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int tegra_pcie_get_resources(struct tegra_pcie *pcie)
{
	struct device *dev = pcie->dev;
	struct platform_device *pdev = to_platform_device(dev);
	struct resource *pads, *afi, *res;
	const struct tegra_pcie_soc *soc = pcie->soc;
	int err;

	err = tegra_pcie_clocks_get(pcie);
	if (err) {
		dev_err(dev, "failed to get clocks: %d\n", err);
		return err;
	}

	err = tegra_pcie_resets_get(pcie);
	if (err) {
		dev_err(dev, "failed to get resets: %d\n", err);
		return err;
	}

	if (soc->program_uphy) {
		err = tegra_pcie_phys_get(pcie);
		if (err < 0) {
			dev_err(dev, "failed to get PHYs: %d\n", err);
			return err;
		}
	}

	pads = platform_get_resource_byname(pdev, IORESOURCE_MEM, "pads");
	pcie->pads = devm_ioremap_resource(dev, pads);
	if (IS_ERR(pcie->pads)) {
		err = PTR_ERR(pcie->pads);
		goto phys_put;
	}

	afi = platform_get_resource_byname(pdev, IORESOURCE_MEM, "afi");
	pcie->afi = devm_ioremap_resource(dev, afi);
	if (IS_ERR(pcie->afi)) {
		err = PTR_ERR(pcie->afi);
		goto phys_put;
	}

	/* request configuration space, but remap later, on demand */
	res = platform_get_resource_byname(pdev, IORESOURCE_MEM, "cs");
	if (!res) {
		err = -EADDRNOTAVAIL;
		goto phys_put;
	}

	pcie->cs = *res;

	/* constrain configuration space to 4 KiB */
	pcie->cs.end = pcie->cs.start + SZ_4K - 1;

	pcie->cfg = devm_ioremap_resource(dev, &pcie->cs);
	if (IS_ERR(pcie->cfg)) {
		err = PTR_ERR(pcie->cfg);
		goto phys_put;
	}

	/* request interrupt */
	err = platform_get_irq_byname(pdev, "intr");
	if (err < 0) {
		dev_err(dev, "failed to get IRQ: %d\n", err);
		goto phys_put;
	}

	pcie->irq = err;

	err = request_irq(pcie->irq, tegra_pcie_isr, IRQF_SHARED, "PCIE", pcie);
	if (err) {
		dev_err(dev, "failed to register IRQ: %d\n", err);
		goto phys_put;
	}

	return 0;

phys_put:
	if (soc->program_uphy)
		tegra_pcie_phys_put(pcie);
	return err;
}