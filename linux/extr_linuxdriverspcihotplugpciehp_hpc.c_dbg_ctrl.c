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
typedef  int /*<<< orphan*/  u16 ;
struct pci_dev {int dummy; } ;
struct controller {int /*<<< orphan*/  slot_cap; TYPE_1__* pcie; } ;
struct TYPE_2__ {struct pci_dev* port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_SLTCTL ; 
 int /*<<< orphan*/  PCI_EXP_SLTSTA ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pciehp_debug ; 

__attribute__((used)) static inline void dbg_ctrl(struct controller *ctrl)
{
	struct pci_dev *pdev = ctrl->pcie->port;
	u16 reg16;

	if (!pciehp_debug)
		return;

	ctrl_info(ctrl, "Slot Capabilities      : 0x%08x\n", ctrl->slot_cap);
	pcie_capability_read_word(pdev, PCI_EXP_SLTSTA, &reg16);
	ctrl_info(ctrl, "Slot Status            : 0x%04x\n", reg16);
	pcie_capability_read_word(pdev, PCI_EXP_SLTCTL, &reg16);
	ctrl_info(ctrl, "Slot Control           : 0x%04x\n", reg16);
}