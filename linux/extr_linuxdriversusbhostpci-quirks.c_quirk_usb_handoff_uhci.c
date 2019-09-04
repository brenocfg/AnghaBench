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
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 
 int PCI_ROM_RESOURCE ; 
 int pci_resource_flags (struct pci_dev*,int) ; 
 unsigned long pci_resource_start (struct pci_dev*,int) ; 
 int /*<<< orphan*/  pio_enabled (struct pci_dev*) ; 
 int /*<<< orphan*/  uhci_check_and_reset_hc (struct pci_dev*,unsigned long) ; 

__attribute__((used)) static void quirk_usb_handoff_uhci(struct pci_dev *pdev)
{
	unsigned long base = 0;
	int i;

	if (!pio_enabled(pdev))
		return;

	for (i = 0; i < PCI_ROM_RESOURCE; i++)
		if ((pci_resource_flags(pdev, i) & IORESOURCE_IO)) {
			base = pci_resource_start(pdev, i);
			break;
		}

	if (base)
		uhci_check_and_reset_hc(pdev, base);
}