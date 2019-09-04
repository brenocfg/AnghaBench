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
struct pci_dev {int /*<<< orphan*/  bus; int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int __pci_reset_bus (int /*<<< orphan*/ ) ; 
 int __pci_reset_slot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_probe_reset_slot (int /*<<< orphan*/ ) ; 

int pci_reset_bus(struct pci_dev *pdev)
{
	return (!pci_probe_reset_slot(pdev->slot)) ?
	    __pci_reset_slot(pdev->slot) : __pci_reset_bus(pdev->bus);
}