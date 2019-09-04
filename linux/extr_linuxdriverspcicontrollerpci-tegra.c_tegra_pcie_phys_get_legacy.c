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
struct tegra_pcie {int legacy_phy; int /*<<< orphan*/  phy; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  devm_phy_optional_get (struct device*,char*) ; 
 int phy_init (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_pcie_phys_get_legacy(struct tegra_pcie *pcie)
{
	struct device *dev = pcie->dev;
	int err;

	pcie->phy = devm_phy_optional_get(dev, "pcie");
	if (IS_ERR(pcie->phy)) {
		err = PTR_ERR(pcie->phy);
		dev_err(dev, "failed to get PHY: %d\n", err);
		return err;
	}

	err = phy_init(pcie->phy);
	if (err < 0) {
		dev_err(dev, "failed to initialize PHY: %d\n", err);
		return err;
	}

	pcie->legacy_phy = true;

	return 0;
}