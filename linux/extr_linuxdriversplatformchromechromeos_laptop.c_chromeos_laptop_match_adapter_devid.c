#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct pci_dev {int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ PCI_DEVID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_is_pci (struct device*) ; 
 struct pci_dev* to_pci_dev (struct device*) ; 

__attribute__((used)) static bool chromeos_laptop_match_adapter_devid(struct device *dev, u32 devid)
{
	struct pci_dev *pdev;

	if (!dev_is_pci(dev))
		return false;

	pdev = to_pci_dev(dev);
	return devid == PCI_DEVID(pdev->bus->number, pdev->devfn);
}