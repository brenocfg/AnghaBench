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
struct phy_provider {int /*<<< orphan*/  dev; } ;
struct phy {int /*<<< orphan*/  dev; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct mdio_device {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct phy_provider*) ; 
 int PTR_ERR (struct phy_provider*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct phy_provider* devm_of_phy_provider_register (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct phy_provider* devm_phy_create (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ns2_pci_phy_ops ; 
 int /*<<< orphan*/  of_phy_simple_xlate ; 
 int /*<<< orphan*/  phy_set_drvdata (struct phy_provider*,struct mdio_device*) ; 

__attribute__((used)) static int ns2_pci_phy_probe(struct mdio_device *mdiodev)
{
	struct device *dev = &mdiodev->dev;
	struct phy_provider *provider;
	struct phy *phy;

	phy = devm_phy_create(dev, dev->of_node, &ns2_pci_phy_ops);
	if (IS_ERR(phy)) {
		dev_err(dev, "failed to create Phy\n");
		return PTR_ERR(phy);
	}

	phy_set_drvdata(phy, mdiodev);

	provider = devm_of_phy_provider_register(&phy->dev,
						 of_phy_simple_xlate);
	if (IS_ERR(provider)) {
		dev_err(dev, "failed to register Phy provider\n");
		return PTR_ERR(provider);
	}

	dev_info(dev, "%s PHY registered\n", dev_name(dev));

	return 0;
}