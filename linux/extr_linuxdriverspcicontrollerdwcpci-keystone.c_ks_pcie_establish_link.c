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
struct pcie_port {int dummy; } ;
struct keystone_pcie {struct dw_pcie* pci; } ;
struct dw_pcie {struct device* dev; struct pcie_port pp; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ dw_pcie_link_up (struct dw_pcie*) ; 
 int /*<<< orphan*/  dw_pcie_setup_rc (struct pcie_port*) ; 
 int /*<<< orphan*/  dw_pcie_wait_for_link (struct dw_pcie*) ; 
 int /*<<< orphan*/  ks_dw_pcie_initiate_link_train (struct keystone_pcie*) ; 

__attribute__((used)) static int ks_pcie_establish_link(struct keystone_pcie *ks_pcie)
{
	struct dw_pcie *pci = ks_pcie->pci;
	struct pcie_port *pp = &pci->pp;
	struct device *dev = pci->dev;
	unsigned int retries;

	dw_pcie_setup_rc(pp);

	if (dw_pcie_link_up(pci)) {
		dev_info(dev, "Link already up\n");
		return 0;
	}

	/* check if the link is up or not */
	for (retries = 0; retries < 5; retries++) {
		ks_dw_pcie_initiate_link_train(ks_pcie);
		if (!dw_pcie_wait_for_link(pci))
			return 0;
	}

	dev_err(dev, "phy link never came up\n");
	return -ETIMEDOUT;
}