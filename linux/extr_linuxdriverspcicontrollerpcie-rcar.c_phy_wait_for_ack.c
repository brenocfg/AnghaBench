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
struct rcar_pcie {struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  H1_PCIEPHYADRR ; 
 int PHY_ACK ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int rcar_pci_read_reg (struct rcar_pcie*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int phy_wait_for_ack(struct rcar_pcie *pcie)
{
	struct device *dev = pcie->dev;
	unsigned int timeout = 100;

	while (timeout--) {
		if (rcar_pci_read_reg(pcie, H1_PCIEPHYADRR) & PHY_ACK)
			return 0;

		udelay(100);
	}

	dev_err(dev, "Access to PCIe phy timed out\n");

	return -ETIMEDOUT;
}