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
struct pci_dev {int pcie_mpss; scalar_t__ is_virtfn; } ;

/* Variables and functions */
 scalar_t__ PCIE_BUS_DEFAULT ; 
 scalar_t__ PCIE_BUS_TUNE_OFF ; 
 scalar_t__ PCI_EXP_TYPE_ROOT_PORT ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,int,int,int) ; 
 int /*<<< orphan*/  pci_is_pcie (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 scalar_t__ pci_pcie_type (struct pci_dev*) ; 
 struct pci_dev* pci_upstream_bridge (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_warn (struct pci_dev*,char*,int,...) ; 
 scalar_t__ pcie_bus_config ; 
 int pcie_get_mps (struct pci_dev*) ; 
 int pcie_set_mps (struct pci_dev*,int) ; 

__attribute__((used)) static void pci_configure_mps(struct pci_dev *dev)
{
	struct pci_dev *bridge = pci_upstream_bridge(dev);
	int mps, mpss, p_mps, rc;

	if (!pci_is_pcie(dev) || !bridge || !pci_is_pcie(bridge))
		return;

	/* MPS and MRRS fields are of type 'RsvdP' for VFs, short-circuit out */
	if (dev->is_virtfn)
		return;

	mps = pcie_get_mps(dev);
	p_mps = pcie_get_mps(bridge);

	if (mps == p_mps)
		return;

	if (pcie_bus_config == PCIE_BUS_TUNE_OFF) {
		pci_warn(dev, "Max Payload Size %d, but upstream %s set to %d; if necessary, use \"pci=pcie_bus_safe\" and report a bug\n",
			 mps, pci_name(bridge), p_mps);
		return;
	}

	/*
	 * Fancier MPS configuration is done later by
	 * pcie_bus_configure_settings()
	 */
	if (pcie_bus_config != PCIE_BUS_DEFAULT)
		return;

	mpss = 128 << dev->pcie_mpss;
	if (mpss < p_mps && pci_pcie_type(bridge) == PCI_EXP_TYPE_ROOT_PORT) {
		pcie_set_mps(bridge, mpss);
		pci_info(dev, "Upstream bridge's Max Payload Size set to %d (was %d, max %d)\n",
			 mpss, p_mps, 128 << bridge->pcie_mpss);
		p_mps = pcie_get_mps(bridge);
	}

	rc = pcie_set_mps(dev, p_mps);
	if (rc) {
		pci_warn(dev, "can't set Max Payload Size to %d; if necessary, use \"pci=pcie_bus_safe\" and report a bug\n",
			 p_mps);
		return;
	}

	pci_info(dev, "Max Payload Size set to %d (was %d, max %d)\n",
		 p_mps, mps, mpss);
}