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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct pcie_device {struct pci_dev* port; } ;
struct pci_dev {scalar_t__ broken_cmd_compl; scalar_t__ is_thunderbolt; scalar_t__ hotplug_user_indicators; } ;
struct controller {int slot_cap; int link_active_reporting; int /*<<< orphan*/  slot; int /*<<< orphan*/  queue; int /*<<< orphan*/  requester; int /*<<< orphan*/  reset_lock; int /*<<< orphan*/  ctrl_lock; struct pcie_device* pcie; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PCI_EXP_LNKCAP ; 
 int PCI_EXP_LNKCAP_DLLLARC ; 
 int /*<<< orphan*/  PCI_EXP_SLTCAP ; 
 int PCI_EXP_SLTCAP_ABP ; 
 int PCI_EXP_SLTCAP_AIP ; 
 int PCI_EXP_SLTCAP_EIP ; 
 int PCI_EXP_SLTCAP_HPC ; 
 int PCI_EXP_SLTCAP_HPS ; 
 int PCI_EXP_SLTCAP_MRLSP ; 
 int PCI_EXP_SLTCAP_NCCS ; 
 int PCI_EXP_SLTCAP_PCP ; 
 int PCI_EXP_SLTCAP_PIP ; 
 int PCI_EXP_SLTCAP_PSN ; 
 int /*<<< orphan*/  PCI_EXP_SLTSTA ; 
 int PCI_EXP_SLTSTA_ABP ; 
 int PCI_EXP_SLTSTA_CC ; 
 int PCI_EXP_SLTSTA_DLLSC ; 
 int PCI_EXP_SLTSTA_MRLSC ; 
 int PCI_EXP_SLTSTA_PDC ; 
 int PCI_EXP_SLTSTA_PFD ; 
 scalar_t__ POWER_CTRL (struct controller*) ; 
 int /*<<< orphan*/  ctrl_info (struct controller*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dbg_ctrl (struct controller*) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct controller*) ; 
 struct controller* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_capability_read_dword (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  pcie_capability_write_word (struct pci_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcie_disable_notification (struct controller*) ; 
 scalar_t__ pcie_init_slot (struct controller*) ; 
 int /*<<< orphan*/  pciehp_get_adapter_status (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pciehp_get_power_status (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  pciehp_power_off_slot (int /*<<< orphan*/ ) ; 

struct controller *pcie_init(struct pcie_device *dev)
{
	struct controller *ctrl;
	u32 slot_cap, link_cap;
	u8 occupied, poweron;
	struct pci_dev *pdev = dev->port;

	ctrl = kzalloc(sizeof(*ctrl), GFP_KERNEL);
	if (!ctrl)
		goto abort;

	ctrl->pcie = dev;
	pcie_capability_read_dword(pdev, PCI_EXP_SLTCAP, &slot_cap);

	if (pdev->hotplug_user_indicators)
		slot_cap &= ~(PCI_EXP_SLTCAP_AIP | PCI_EXP_SLTCAP_PIP);

	/*
	 * We assume no Thunderbolt controllers support Command Complete events,
	 * but some controllers falsely claim they do.
	 */
	if (pdev->is_thunderbolt)
		slot_cap |= PCI_EXP_SLTCAP_NCCS;

	ctrl->slot_cap = slot_cap;
	mutex_init(&ctrl->ctrl_lock);
	init_rwsem(&ctrl->reset_lock);
	init_waitqueue_head(&ctrl->requester);
	init_waitqueue_head(&ctrl->queue);
	dbg_ctrl(ctrl);

	/* Check if Data Link Layer Link Active Reporting is implemented */
	pcie_capability_read_dword(pdev, PCI_EXP_LNKCAP, &link_cap);
	if (link_cap & PCI_EXP_LNKCAP_DLLLARC)
		ctrl->link_active_reporting = 1;

	/* Clear all remaining event bits in Slot Status register. */
	pcie_capability_write_word(pdev, PCI_EXP_SLTSTA,
		PCI_EXP_SLTSTA_ABP | PCI_EXP_SLTSTA_PFD |
		PCI_EXP_SLTSTA_MRLSC | PCI_EXP_SLTSTA_CC |
		PCI_EXP_SLTSTA_DLLSC | PCI_EXP_SLTSTA_PDC);

	ctrl_info(ctrl, "Slot #%d AttnBtn%c PwrCtrl%c MRL%c AttnInd%c PwrInd%c HotPlug%c Surprise%c Interlock%c NoCompl%c LLActRep%c%s\n",
		(slot_cap & PCI_EXP_SLTCAP_PSN) >> 19,
		FLAG(slot_cap, PCI_EXP_SLTCAP_ABP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_PCP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_MRLSP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_AIP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_PIP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_HPC),
		FLAG(slot_cap, PCI_EXP_SLTCAP_HPS),
		FLAG(slot_cap, PCI_EXP_SLTCAP_EIP),
		FLAG(slot_cap, PCI_EXP_SLTCAP_NCCS),
		FLAG(link_cap, PCI_EXP_LNKCAP_DLLLARC),
		pdev->broken_cmd_compl ? " (with Cmd Compl erratum)" : "");

	if (pcie_init_slot(ctrl))
		goto abort_ctrl;

	/*
	 * If empty slot's power status is on, turn power off.  The IRQ isn't
	 * requested yet, so avoid triggering a notification with this command.
	 */
	if (POWER_CTRL(ctrl)) {
		pciehp_get_adapter_status(ctrl->slot, &occupied);
		pciehp_get_power_status(ctrl->slot, &poweron);
		if (!occupied && poweron) {
			pcie_disable_notification(ctrl);
			pciehp_power_off_slot(ctrl->slot);
		}
	}

	return ctrl;

abort_ctrl:
	kfree(ctrl);
abort:
	return NULL;
}