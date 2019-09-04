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
struct slot {int physical_path; TYPE_1__* pci_bus; } ;
struct pcibus_info {int pbi_enabled_devices; } ;
struct pcibr_slot_disable_resp {int /*<<< orphan*/  resp_sub_errno; int /*<<< orphan*/  resp_l1_msg; } ;
struct hotplug_slot {struct slot* private; } ;
struct TYPE_2__ {int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int EIO ; 
 int EPERM ; 
 int PCI_EMPTY_33MHZ ; 
 int PCI_L1_ERR ; 
 int PCI_REQ_SLOT_DISABLE ; 
 int PCI_REQ_SLOT_ELIGIBLE ; 
 int PCI_SLOT_ALREADY_DOWN ; 
 struct pcibus_info* SN_PCIBUS_BUSSOFT_INFO (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int sal_pcibr_slot_disable (struct pcibus_info*,int,int,struct pcibr_slot_disable_resp*) ; 

__attribute__((used)) static int sn_slot_disable(struct hotplug_slot *bss_hotplug_slot,
			   int device_num, int action)
{
	struct slot *slot = bss_hotplug_slot->private;
	struct pcibus_info *pcibus_info;
	struct pcibr_slot_disable_resp resp;
	int rc;

	pcibus_info = SN_PCIBUS_BUSSOFT_INFO(slot->pci_bus);

	rc = sal_pcibr_slot_disable(pcibus_info, device_num, action, &resp);

	if ((action == PCI_REQ_SLOT_ELIGIBLE) &&
	    (rc == PCI_SLOT_ALREADY_DOWN)) {
		pci_dbg(slot->pci_bus->self, "Slot %s already inactive\n", slot->physical_path);
		return 1; /* return 1 to user */
	}

	if ((action == PCI_REQ_SLOT_ELIGIBLE) && (rc == PCI_EMPTY_33MHZ)) {
		pci_dbg(slot->pci_bus->self, "Cannot remove last 33MHz card\n");
		return -EPERM;
	}

	if ((action == PCI_REQ_SLOT_ELIGIBLE) && (rc == PCI_L1_ERR)) {
		pci_dbg(slot->pci_bus->self, "L1 failure %d with message \n%s\n",
			resp.resp_sub_errno, resp.resp_l1_msg);
		return -EPERM;
	}

	if ((action == PCI_REQ_SLOT_ELIGIBLE) && rc) {
		pci_dbg(slot->pci_bus->self, "remove failed with error %d sub-error %d\n",
			rc, resp.resp_sub_errno);
		return -EIO;
	}

	if ((action == PCI_REQ_SLOT_ELIGIBLE) && !rc)
		return 0;

	if ((action == PCI_REQ_SLOT_DISABLE) && !rc) {
		pcibus_info = SN_PCIBUS_BUSSOFT_INFO(slot->pci_bus);
		pcibus_info->pbi_enabled_devices &= ~(1 << device_num);
		pci_dbg(slot->pci_bus->self, "remove successful\n");
		return 0;
	}

	if ((action == PCI_REQ_SLOT_DISABLE) && rc) {
		pci_dbg(slot->pci_bus->self, "remove failed rc = %d\n", rc);
	}

	return rc;
}