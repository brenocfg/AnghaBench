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
typedef  int u8 ;
typedef  int u16 ;
struct slot {int /*<<< orphan*/  ctrl; } ;
struct pci_dev {int dummy; } ;
struct hotplug_slot {struct slot* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_SLTCTL ; 
 int PCI_EXP_SLTCTL_AIC ; 
 int PCI_EXP_SLTCTL_PIC ; 
 struct pci_dev* ctrl_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_config_pm_runtime_get (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_config_pm_runtime_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

int pciehp_get_raw_indicator_status(struct hotplug_slot *hotplug_slot,
				    u8 *status)
{
	struct slot *slot = hotplug_slot->private;
	struct pci_dev *pdev = ctrl_dev(slot->ctrl);
	u16 slot_ctrl;

	pci_config_pm_runtime_get(pdev);
	pcie_capability_read_word(pdev, PCI_EXP_SLTCTL, &slot_ctrl);
	pci_config_pm_runtime_put(pdev);
	*status = (slot_ctrl & (PCI_EXP_SLTCTL_AIC | PCI_EXP_SLTCTL_PIC)) >> 6;
	return 0;
}