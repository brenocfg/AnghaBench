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
struct pcifront_device {TYPE_1__* xdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int pci_xen_swiotlb_init_late () ; 
 struct pcifront_device* pcifront_dev ; 
 int /*<<< orphan*/  pcifront_dev_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swiotlb_nr_tbl () ; 

__attribute__((used)) static int pcifront_connect_and_init_dma(struct pcifront_device *pdev)
{
	int err = 0;

	spin_lock(&pcifront_dev_lock);

	if (!pcifront_dev) {
		dev_info(&pdev->xdev->dev, "Installing PCI frontend\n");
		pcifront_dev = pdev;
	} else
		err = -EEXIST;

	spin_unlock(&pcifront_dev_lock);

	if (!err && !swiotlb_nr_tbl()) {
		err = pci_xen_swiotlb_init_late();
		if (err)
			dev_err(&pdev->xdev->dev, "Could not setup SWIOTLB!\n");
	}
	return err;
}