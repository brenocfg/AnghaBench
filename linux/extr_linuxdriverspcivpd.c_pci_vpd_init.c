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
typedef  scalar_t__ u8 ;
struct pci_vpd {scalar_t__ valid; scalar_t__ busy; scalar_t__ cap; int /*<<< orphan*/  lock; int /*<<< orphan*/ * ops; int /*<<< orphan*/  len; } ;
struct pci_dev {int dev_flags; struct pci_vpd* vpd; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  PCI_CAP_ID_VPD ; 
 int PCI_DEV_FLAGS_VPD_REF_F0 ; 
 int /*<<< orphan*/  PCI_VPD_MAX_SIZE ; 
 struct pci_vpd* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 scalar_t__ pci_find_capability (struct pci_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_vpd_f0_ops ; 
 int /*<<< orphan*/  pci_vpd_ops ; 

int pci_vpd_init(struct pci_dev *dev)
{
	struct pci_vpd *vpd;
	u8 cap;

	cap = pci_find_capability(dev, PCI_CAP_ID_VPD);
	if (!cap)
		return -ENODEV;

	vpd = kzalloc(sizeof(*vpd), GFP_ATOMIC);
	if (!vpd)
		return -ENOMEM;

	vpd->len = PCI_VPD_MAX_SIZE;
	if (dev->dev_flags & PCI_DEV_FLAGS_VPD_REF_F0)
		vpd->ops = &pci_vpd_f0_ops;
	else
		vpd->ops = &pci_vpd_ops;
	mutex_init(&vpd->lock);
	vpd->cap = cap;
	vpd->busy = 0;
	vpd->valid = 0;
	dev->vpd = vpd;
	return 0;
}