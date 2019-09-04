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
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  piix4_pm_io_region ; 
 int /*<<< orphan*/ * piix4_poweroff ; 
 int /*<<< orphan*/ * pm_dev ; 
 int /*<<< orphan*/ * pm_power_off ; 

__attribute__((used)) static void piix4_poweroff_remove(struct pci_dev *dev)
{
	if (pm_power_off == piix4_poweroff)
		pm_power_off = NULL;

	pci_release_region(dev, piix4_pm_io_region);
	pm_dev = NULL;
}