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
typedef  scalar_t__ u16 ;
struct pci_dev {TYPE_1__* sriov; int /*<<< orphan*/  is_physfn; } ;
struct TYPE_2__ {scalar_t__ total_VFs; int ctrl; scalar_t__ driver_max_VFs; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOSYS ; 
 int PCI_SRIOV_CTRL_VFE ; 

int pci_sriov_set_totalvfs(struct pci_dev *dev, u16 numvfs)
{
	if (!dev->is_physfn)
		return -ENOSYS;

	if (numvfs > dev->sriov->total_VFs)
		return -EINVAL;

	/* Shouldn't change if VFs already enabled */
	if (dev->sriov->ctrl & PCI_SRIOV_CTRL_VFE)
		return -EBUSY;

	dev->sriov->driver_max_VFs = numvfs;
	return 0;
}