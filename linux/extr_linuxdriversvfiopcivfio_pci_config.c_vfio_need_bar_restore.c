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
typedef  scalar_t__ u32 ;
struct vfio_pci_device {scalar_t__* rbar; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int PCI_BASE_ADDRESS_0 ; 
 int PCI_BASE_ADDRESS_5 ; 
 int pci_user_read_config_dword (int /*<<< orphan*/ ,int,scalar_t__*) ; 

__attribute__((used)) static bool vfio_need_bar_restore(struct vfio_pci_device *vdev)
{
	int i = 0, pos = PCI_BASE_ADDRESS_0, ret;
	u32 bar;

	for (; pos <= PCI_BASE_ADDRESS_5; i++, pos += 4) {
		if (vdev->rbar[i]) {
			ret = pci_user_read_config_dword(vdev->pdev, pos, &bar);
			if (ret || vdev->rbar[i] != bar)
				return true;
		}
	}

	return false;
}