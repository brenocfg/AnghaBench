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
typedef  int u32 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTEL_MPC_REG ; 
 int INTEL_MPC_REG_IRBNCE ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int /*<<< orphan*/  pci_read_config_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pci_quirk_enable_intel_rp_mpc_acs(struct pci_dev *dev)
{
	u32 mpc;

	/*
	 * When enabled, the IRBNCE bit of the MPC register enables the
	 * equivalent of PCI ACS Source Validation (PCI_ACS_SV), which
	 * ensures that requester IDs fall within the bus number range
	 * of the bridge.  Enable if not already.
	 */
	pci_read_config_dword(dev, INTEL_MPC_REG, &mpc);
	if (!(mpc & INTEL_MPC_REG_IRBNCE)) {
		pci_info(dev, "Enabling MPC IRBNCE\n");
		mpc |= INTEL_MPC_REG_IRBNCE;
		pci_write_config_word(dev, INTEL_MPC_REG, mpc);
	}
}