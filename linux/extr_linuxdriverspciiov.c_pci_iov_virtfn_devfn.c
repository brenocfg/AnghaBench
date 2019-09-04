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
struct pci_dev {int devfn; TYPE_1__* sriov; int /*<<< orphan*/  is_physfn; } ;
struct TYPE_2__ {int offset; int stride; } ;

/* Variables and functions */
 int EINVAL ; 

int pci_iov_virtfn_devfn(struct pci_dev *dev, int vf_id)
{
	if (!dev->is_physfn)
		return -EINVAL;
	return (dev->devfn + dev->sriov->offset +
		dev->sriov->stride * vf_id) & 0xff;
}