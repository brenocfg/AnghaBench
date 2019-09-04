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
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_D3hot ; 

__attribute__((used)) static pci_power_t mid_pci_choose_state(struct pci_dev *pdev)
{
	return PCI_D3hot;
}