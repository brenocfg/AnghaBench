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
struct pci_dev {int /*<<< orphan*/  dev; scalar_t__ reset_fn; } ;

/* Variables and functions */
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcie_aspm_create_sysfs_dev_files (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_aspm_remove_sysfs_dev_files (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_vpd_create_sysfs_dev_files (struct pci_dev*) ; 
 int /*<<< orphan*/  pcie_vpd_remove_sysfs_dev_files (struct pci_dev*) ; 
 int /*<<< orphan*/  reset_attr ; 

__attribute__((used)) static int pci_create_capabilities_sysfs(struct pci_dev *dev)
{
	int retval;

	pcie_vpd_create_sysfs_dev_files(dev);
	pcie_aspm_create_sysfs_dev_files(dev);

	if (dev->reset_fn) {
		retval = device_create_file(&dev->dev, &reset_attr);
		if (retval)
			goto error;
	}
	return 0;

error:
	pcie_aspm_remove_sysfs_dev_files(dev);
	pcie_vpd_remove_sysfs_dev_files(dev);
	return retval;
}