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
struct pci_dev {int /*<<< orphan*/  current_state; int /*<<< orphan*/  pm_cap; } ;
typedef  int /*<<< orphan*/  pci_power_t ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCI_D0 ; 
 int /*<<< orphan*/  pci_update_current_state (struct pci_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ platform_pci_power_manageable (struct pci_dev*) ; 
 int platform_pci_set_power_state (struct pci_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pci_platform_power_transition(struct pci_dev *dev, pci_power_t state)
{
	int error;

	if (platform_pci_power_manageable(dev)) {
		error = platform_pci_set_power_state(dev, state);
		if (!error)
			pci_update_current_state(dev, state);
	} else
		error = -ENODEV;

	if (error && !dev->pm_cap) /* Fall back to PCI_D0 */
		dev->current_state = PCI_D0;

	return error;
}