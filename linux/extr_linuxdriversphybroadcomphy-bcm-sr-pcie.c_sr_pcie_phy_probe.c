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
struct sr_pcie_phy_core {struct sr_pcie_phy* phys; int /*<<< orphan*/  pipemux; struct device* dev; struct phy_provider* mhb; struct phy_provider* cdru; struct phy_provider* base; } ;
struct sr_pcie_phy {unsigned int index; struct phy_provider* phy; struct sr_pcie_phy_core* core; } ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct phy_provider {int dummy; } ;
struct phy_ops {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 unsigned int SR_NR_PCIE_PHYS ; 
 unsigned int SR_PAXC_PHY_IDX ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct sr_pcie_phy_core*) ; 
 struct phy_provider* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct sr_pcie_phy_core* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_of_phy_provider_register (struct device*,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ *,struct phy_ops const*) ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct sr_pcie_phy*) ; 
 int /*<<< orphan*/  pipemux_strap_is_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipemux_strap_read (struct sr_pcie_phy_core*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct phy_ops sr_paxc_phy_ops ; 
 struct phy_ops sr_pcie_phy_ops ; 
 int /*<<< orphan*/  sr_pcie_phy_xlate ; 
 void* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int sr_pcie_phy_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	struct sr_pcie_phy_core *core;
	struct resource *res;
	struct phy_provider *provider;
	unsigned int phy_idx = 0;

	core = devm_kzalloc(dev, sizeof(*core), GFP_KERNEL);
	if (!core)
		return -ENOMEM;

	core->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	core->base = devm_ioremap_resource(core->dev, res);
	if (IS_ERR(core->base))
		return PTR_ERR(core->base);

	core->cdru = syscon_regmap_lookup_by_phandle(node, "brcm,sr-cdru");
	if (IS_ERR(core->cdru)) {
		dev_err(core->dev, "unable to find CDRU device\n");
		return PTR_ERR(core->cdru);
	}

	core->mhb = syscon_regmap_lookup_by_phandle(node, "brcm,sr-mhb");
	if (IS_ERR(core->mhb)) {
		dev_err(core->dev, "unable to find MHB device\n");
		return PTR_ERR(core->mhb);
	}

	/* read the PCIe PIPEMUX strap setting */
	core->pipemux = pipemux_strap_read(core);
	if (!pipemux_strap_is_valid(core->pipemux)) {
		dev_err(core->dev, "invalid PCIe PIPEMUX strap %u\n",
			core->pipemux);
		return -EIO;
	}

	for (phy_idx = 0; phy_idx < SR_NR_PCIE_PHYS; phy_idx++) {
		struct sr_pcie_phy *p = &core->phys[phy_idx];
		const struct phy_ops *ops;

		if (phy_idx == SR_PAXC_PHY_IDX)
			ops = &sr_paxc_phy_ops;
		else
			ops = &sr_pcie_phy_ops;

		p->phy = devm_phy_create(dev, NULL, ops);
		if (IS_ERR(p->phy)) {
			dev_err(dev, "failed to create PCIe PHY\n");
			return PTR_ERR(p->phy);
		}

		p->core = core;
		p->index = phy_idx;
		phy_set_drvdata(p->phy, p);
	}

	dev_set_drvdata(dev, core);

	provider = devm_of_phy_provider_register(dev, sr_pcie_phy_xlate);
	if (IS_ERR(provider)) {
		dev_err(dev, "failed to register PHY provider\n");
		return PTR_ERR(provider);
	}

	dev_info(dev, "Stingray PCIe PHY driver initialized\n");

	return 0;
}