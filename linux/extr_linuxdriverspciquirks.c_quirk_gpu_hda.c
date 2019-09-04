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
struct pci_dev {int class; int /*<<< orphan*/  dev; int /*<<< orphan*/  devfn; TYPE_1__* bus; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int DL_FLAG_PM_RUNTIME ; 
 int DL_FLAG_STATELESS ; 
 int PCI_BASE_CLASS_DISPLAY ; 
 int /*<<< orphan*/  PCI_DEVFN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCI_FUNC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PCI_SLOT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_link_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_domain_nr (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_err (struct pci_dev*,char*,int /*<<< orphan*/ ) ; 
 struct pci_dev* pci_get_domain_bus_and_slot (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_name (struct pci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_allow (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void quirk_gpu_hda(struct pci_dev *hda)
{
	struct pci_dev *gpu;

	if (PCI_FUNC(hda->devfn) != 1)
		return;

	gpu = pci_get_domain_bus_and_slot(pci_domain_nr(hda->bus),
					  hda->bus->number,
					  PCI_DEVFN(PCI_SLOT(hda->devfn), 0));
	if (!gpu || (gpu->class >> 16) != PCI_BASE_CLASS_DISPLAY) {
		pci_dev_put(gpu);
		return;
	}

	if (!device_link_add(&hda->dev, &gpu->dev,
			     DL_FLAG_STATELESS | DL_FLAG_PM_RUNTIME))
		pci_err(hda, "cannot link HDA to GPU %s\n", pci_name(gpu));

	pm_runtime_allow(&hda->dev);
	pci_dev_put(gpu);
}