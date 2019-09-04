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
typedef  int u16 ;
struct esas2r_adapter {int /*<<< orphan*/  pcid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESAS2R_LOG_INFO ; 
 int /*<<< orphan*/  PCI_CAP_ID_EXP ; 
 scalar_t__ PCI_EXP_DEVCTL ; 
 int PCI_EXP_DEVCTL_READRQ ; 
 int PCI_EXP_DEVCTL_READRQ_512B ; 
 int /*<<< orphan*/  esas2r_log (int /*<<< orphan*/ ,char*) ; 
 int pci_find_capability (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_word (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 int /*<<< orphan*/  pci_write_config_word (int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static void esas2r_init_pci_cfg_space(struct esas2r_adapter *a)
{
	int pcie_cap_reg;

	pcie_cap_reg = pci_find_capability(a->pcid, PCI_CAP_ID_EXP);
	if (pcie_cap_reg) {
		u16 devcontrol;

		pci_read_config_word(a->pcid, pcie_cap_reg + PCI_EXP_DEVCTL,
				     &devcontrol);

		if ((devcontrol & PCI_EXP_DEVCTL_READRQ) >
		     PCI_EXP_DEVCTL_READRQ_512B) {
			esas2r_log(ESAS2R_LOG_INFO,
				   "max read request size > 512B");

			devcontrol &= ~PCI_EXP_DEVCTL_READRQ;
			devcontrol |= PCI_EXP_DEVCTL_READRQ_512B;
			pci_write_config_word(a->pcid,
					      pcie_cap_reg + PCI_EXP_DEVCTL,
					      devcontrol);
		}
	}
}