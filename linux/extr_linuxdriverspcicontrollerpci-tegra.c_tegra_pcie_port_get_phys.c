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
struct tegra_pcie_port {unsigned int lanes; struct phy** phys; int /*<<< orphan*/  np; TYPE_1__* pcie; } ;
struct phy {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phy ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct phy*) ; 
 int PTR_ERR (struct phy*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,int) ; 
 struct phy** devm_kcalloc (struct device*,int,unsigned int,int /*<<< orphan*/ ) ; 
 struct phy* devm_of_phy_optional_get_index (struct device*,int /*<<< orphan*/ ,char*,unsigned int) ; 
 int phy_init (struct phy*) ; 

__attribute__((used)) static int tegra_pcie_port_get_phys(struct tegra_pcie_port *port)
{
	struct device *dev = port->pcie->dev;
	struct phy *phy;
	unsigned int i;
	int err;

	port->phys = devm_kcalloc(dev, sizeof(phy), port->lanes, GFP_KERNEL);
	if (!port->phys)
		return -ENOMEM;

	for (i = 0; i < port->lanes; i++) {
		phy = devm_of_phy_optional_get_index(dev, port->np, "pcie", i);
		if (IS_ERR(phy)) {
			dev_err(dev, "failed to get PHY#%u: %ld\n", i,
				PTR_ERR(phy));
			return PTR_ERR(phy);
		}

		err = phy_init(phy);
		if (err < 0) {
			dev_err(dev, "failed to initialize PHY#%u: %d\n", i,
				err);
			return err;
		}

		port->phys[i] = phy;
	}

	return 0;
}