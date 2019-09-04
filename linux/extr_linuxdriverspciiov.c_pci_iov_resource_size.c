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
typedef  int /*<<< orphan*/  resource_size_t ;
struct TYPE_2__ {int /*<<< orphan*/ * barsz; } ;

/* Variables and functions */
 int PCI_IOV_RESOURCES ; 

resource_size_t pci_iov_resource_size(struct pci_dev *dev, int resno)
{
	if (!dev->is_physfn)
		return 0;

	return dev->sriov->barsz[resno - PCI_IOV_RESOURCES];
}