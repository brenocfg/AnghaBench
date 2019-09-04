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
 int PCIPCI_TRITON ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*) ; 
 int pci_pci_problems ; 

__attribute__((used)) static void quirk_triton(struct pci_dev *dev)
{
	if ((pci_pci_problems&PCIPCI_TRITON) == 0) {
		pci_info(dev, "Limiting direct PCI/PCI transfers\n");
		pci_pci_problems |= PCIPCI_TRITON;
	}
}