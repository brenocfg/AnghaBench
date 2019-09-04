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
struct pci_dev {int /*<<< orphan*/  irq; } ;
typedef  int /*<<< orphan*/  pci_ers_result_t ;
typedef  enum pci_channel_state { ____Placeholder_pci_channel_state } pci_channel_state ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ERS_RESULT_CAN_RECOVER ; 
 int /*<<< orphan*/  PCI_ERS_RESULT_DISCONNECT ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int pci_channel_io_perm_failure ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  sym2_remove (struct pci_dev*) ; 

__attribute__((used)) static pci_ers_result_t sym2_io_error_detected(struct pci_dev *pdev,
                                         enum pci_channel_state state)
{
	/* If slot is permanently frozen, turn everything off */
	if (state == pci_channel_io_perm_failure) {
		sym2_remove(pdev);
		return PCI_ERS_RESULT_DISCONNECT;
	}

	disable_irq(pdev->irq);
	pci_disable_device(pdev);

	/* Request that MMIO be enabled, so register dump can be taken. */
	return PCI_ERS_RESULT_CAN_RECOVER;
}