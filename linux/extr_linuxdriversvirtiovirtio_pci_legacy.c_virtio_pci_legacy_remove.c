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
struct virtio_pci_device {int /*<<< orphan*/  ioaddr; struct pci_dev* pci_dev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_region (struct pci_dev*,int /*<<< orphan*/ ) ; 

void virtio_pci_legacy_remove(struct virtio_pci_device *vp_dev)
{
	struct pci_dev *pci_dev = vp_dev->pci_dev;

	pci_iounmap(pci_dev, vp_dev->ioaddr);
	pci_release_region(pci_dev, 0);
}