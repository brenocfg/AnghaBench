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
struct pci_dev {int no_msi; struct pci_bus* subordinate; } ;
struct pci_bus {int /*<<< orphan*/  dev; int /*<<< orphan*/  bus_flags; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 int /*<<< orphan*/  PCI_BUS_FLAGS_NO_MSI ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ kstrtoul (char const*,int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,char*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static ssize_t msi_bus_store(struct device *dev, struct device_attribute *attr,
			     const char *buf, size_t count)
{
	struct pci_dev *pdev = to_pci_dev(dev);
	struct pci_bus *subordinate = pdev->subordinate;
	unsigned long val;

	if (kstrtoul(buf, 0, &val) < 0)
		return -EINVAL;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	/*
	 * "no_msi" and "bus_flags" only affect what happens when a driver
	 * requests MSI or MSI-X.  They don't affect any drivers that have
	 * already requested MSI or MSI-X.
	 */
	if (!subordinate) {
		pdev->no_msi = !val;
		pci_info(pdev, "MSI/MSI-X %s for future drivers\n",
			 val ? "allowed" : "disallowed");
		return count;
	}

	if (val)
		subordinate->bus_flags &= ~PCI_BUS_FLAGS_NO_MSI;
	else
		subordinate->bus_flags |= PCI_BUS_FLAGS_NO_MSI;

	dev_info(&subordinate->dev, "MSI/MSI-X %s for future drivers of devices on this bus\n",
		 val ? "allowed" : "disallowed");
	return count;
}