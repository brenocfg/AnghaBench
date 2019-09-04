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
struct tegra_pcie_port {unsigned int lanes; int /*<<< orphan*/ * phys; TYPE_1__* pcie; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,unsigned int,int) ; 
 int phy_power_off (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_pcie_port_phy_power_off(struct tegra_pcie_port *port)
{
	struct device *dev = port->pcie->dev;
	unsigned int i;
	int err;

	for (i = 0; i < port->lanes; i++) {
		err = phy_power_off(port->phys[i]);
		if (err < 0) {
			dev_err(dev, "failed to power off PHY#%u: %d\n", i,
				err);
			return err;
		}
	}

	return 0;
}