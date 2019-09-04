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
struct spear13xx_pcie {int is_gen1; int /*<<< orphan*/  clk; int /*<<< orphan*/  app_base; int /*<<< orphan*/  phy; struct dw_pcie* pci; } ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct dw_pcie {int /*<<< orphan*/  dbi_base; int /*<<< orphan*/ * ops; struct device* dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_pci_remap_cfg_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  devm_phy_get (struct device*,char*) ; 
 int /*<<< orphan*/  dw_pcie_ops ; 
 scalar_t__ of_property_read_bool (struct device_node*,char*) ; 
 int /*<<< orphan*/  phy_init (int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct spear13xx_pcie*) ; 
 int spear13xx_add_pcie_port (struct spear13xx_pcie*,struct platform_device*) ; 

__attribute__((used)) static int spear13xx_pcie_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct dw_pcie *pci;
	struct spear13xx_pcie *spear13xx_pcie;
	struct device_node *np = dev->of_node;
	struct resource *dbi_base;
	int ret;

	spear13xx_pcie = devm_kzalloc(dev, sizeof(*spear13xx_pcie), GFP_KERNEL);
	if (!spear13xx_pcie)
		return -ENOMEM;

	pci = devm_kzalloc(dev, sizeof(*pci), GFP_KERNEL);
	if (!pci)
		return -ENOMEM;

	pci->dev = dev;
	pci->ops = &dw_pcie_ops;

	spear13xx_pcie->pci = pci;

	spear13xx_pcie->phy = devm_phy_get(dev, "pcie-phy");
	if (IS_ERR(spear13xx_pcie->phy)) {
		ret = PTR_ERR(spear13xx_pcie->phy);
		if (ret == -EPROBE_DEFER)
			dev_info(dev, "probe deferred\n");
		else
			dev_err(dev, "couldn't get pcie-phy\n");
		return ret;
	}

	phy_init(spear13xx_pcie->phy);

	spear13xx_pcie->clk = devm_clk_get(dev, NULL);
	if (IS_ERR(spear13xx_pcie->clk)) {
		dev_err(dev, "couldn't get clk for pcie\n");
		return PTR_ERR(spear13xx_pcie->clk);
	}
	ret = clk_prepare_enable(spear13xx_pcie->clk);
	if (ret) {
		dev_err(dev, "couldn't enable clk for pcie\n");
		return ret;
	}

	dbi_base = platform_get_resource_byname(pdev, IORESOURCE_MEM, "dbi");
	pci->dbi_base = devm_pci_remap_cfg_resource(dev, dbi_base);
	if (IS_ERR(pci->dbi_base)) {
		dev_err(dev, "couldn't remap dbi base %p\n", dbi_base);
		ret = PTR_ERR(pci->dbi_base);
		goto fail_clk;
	}
	spear13xx_pcie->app_base = pci->dbi_base + 0x2000;

	if (of_property_read_bool(np, "st,pcie-is-gen1"))
		spear13xx_pcie->is_gen1 = true;

	platform_set_drvdata(pdev, spear13xx_pcie);

	ret = spear13xx_add_pcie_port(spear13xx_pcie, pdev);
	if (ret < 0)
		goto fail_clk;

	return 0;

fail_clk:
	clk_disable_unprepare(spear13xx_pcie->clk);

	return ret;
}