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
struct uhci_hcd {int dummy; } ;
struct pci_dev {scalar_t__ vendor; } ;

/* Variables and functions */
 scalar_t__ PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  USBLEGSUP ; 
 int /*<<< orphan*/  USBLEGSUP_DEFAULT ; 
 int /*<<< orphan*/  USBRES_INTEL ; 
 int /*<<< orphan*/  pci_write_config_byte (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_write_config_word (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pci_dev* to_pci_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_dev (struct uhci_hcd*) ; 

__attribute__((used)) static void uhci_pci_configure_hc(struct uhci_hcd *uhci)
{
	struct pci_dev *pdev = to_pci_dev(uhci_dev(uhci));

	/* Enable PIRQ */
	pci_write_config_word(pdev, USBLEGSUP, USBLEGSUP_DEFAULT);

	/* Disable platform-specific non-PME# wakeup */
	if (pdev->vendor == PCI_VENDOR_ID_INTEL)
		pci_write_config_byte(pdev, USBRES_INTEL, 0);
}