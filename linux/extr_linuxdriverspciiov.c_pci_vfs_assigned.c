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
struct pci_dev {int /*<<< orphan*/  vendor; struct pci_dev* physfn; scalar_t__ is_virtfn; TYPE_1__* sriov; int /*<<< orphan*/  is_physfn; } ;
struct TYPE_2__ {unsigned short vf_device; } ;

/* Variables and functions */
 struct pci_dev* pci_get_device (int /*<<< orphan*/ ,unsigned short,struct pci_dev*) ; 
 scalar_t__ pci_is_dev_assigned (struct pci_dev*) ; 

int pci_vfs_assigned(struct pci_dev *dev)
{
	struct pci_dev *vfdev;
	unsigned int vfs_assigned = 0;
	unsigned short dev_id;

	/* only search if we are a PF */
	if (!dev->is_physfn)
		return 0;

	/*
	 * determine the device ID for the VFs, the vendor ID will be the
	 * same as the PF so there is no need to check for that one
	 */
	dev_id = dev->sriov->vf_device;

	/* loop through all the VFs to see if we own any that are assigned */
	vfdev = pci_get_device(dev->vendor, dev_id, NULL);
	while (vfdev) {
		/*
		 * It is considered assigned if it is a virtual function with
		 * our dev as the physical function and the assigned bit is set
		 */
		if (vfdev->is_virtfn && (vfdev->physfn == dev) &&
			pci_is_dev_assigned(vfdev))
			vfs_assigned++;

		vfdev = pci_get_device(dev->vendor, dev_id, vfdev);
	}

	return vfs_assigned;
}