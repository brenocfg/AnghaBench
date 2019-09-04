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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_EXP_LNKSTA ; 
 int PCI_EXP_LNKSTA_DLLLA ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,char*) ; 
 int /*<<< orphan*/  pcie_capability_read_word (struct pci_dev*,int /*<<< orphan*/ ,int*) ; 

bool pcie_wait_for_link(struct pci_dev *pdev, bool active)
{
	int timeout = 1000;
	bool ret;
	u16 lnk_status;

	for (;;) {
		pcie_capability_read_word(pdev, PCI_EXP_LNKSTA, &lnk_status);
		ret = !!(lnk_status & PCI_EXP_LNKSTA_DLLLA);
		if (ret == active)
			return true;
		if (timeout <= 0)
			break;
		msleep(10);
		timeout -= 10;
	}

	pci_info(pdev, "Data Link Layer Link Active not %s in 1000 msec\n",
		 active ? "set" : "cleared");

	return false;
}