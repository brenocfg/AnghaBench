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
struct pci_dev {TYPE_1__* sriov; int /*<<< orphan*/  is_physfn; } ;
struct TYPE_2__ {int driver_max_VFs; } ;

/* Variables and functions */

int pci_sriov_get_totalvfs(struct pci_dev *dev)
{
	if (!dev->is_physfn)
		return 0;

	return dev->sriov->driver_max_VFs;
}