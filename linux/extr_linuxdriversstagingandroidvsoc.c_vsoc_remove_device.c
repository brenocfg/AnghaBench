#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int device_created; int irq_requested; int /*<<< orphan*/  vector; } ;
struct TYPE_5__ {int msix_enabled; int class_added; int cdev_added; int requested_regions; int enabled_device; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * regs; int /*<<< orphan*/ * kernel_mapped_shm; TYPE_1__* layout; scalar_t__ major; int /*<<< orphan*/  cdev; int /*<<< orphan*/  class; int /*<<< orphan*/ * regions; TYPE_3__* msix_entries; TYPE_3__* regions_data; } ;
struct TYPE_4__ {int region_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (scalar_t__,int) ; 
 int /*<<< orphan*/  cdev_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_disable_msix (struct pci_dev*) ; 
 int /*<<< orphan*/  pci_iounmap (struct pci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_regions (struct pci_dev*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ vsoc_dev ; 

__attribute__((used)) static void vsoc_remove_device(struct pci_dev *pdev)
{
	int i;
	/*
	 * pdev is the first thing to be set on probe and the last thing
	 * to be cleared here. If it's NULL then there is no cleanup.
	 */
	if (!pdev || !vsoc_dev.dev)
		return;
	dev_info(&pdev->dev, "remove_device\n");
	if (vsoc_dev.regions_data) {
		for (i = 0; i < vsoc_dev.layout->region_count; ++i) {
			if (vsoc_dev.regions_data[i].device_created) {
				device_destroy(vsoc_dev.class,
					       MKDEV(vsoc_dev.major, i));
				vsoc_dev.regions_data[i].device_created = false;
			}
			if (vsoc_dev.regions_data[i].irq_requested)
				free_irq(vsoc_dev.msix_entries[i].vector, NULL);
			vsoc_dev.regions_data[i].irq_requested = false;
		}
		kfree(vsoc_dev.regions_data);
		vsoc_dev.regions_data = NULL;
	}
	if (vsoc_dev.msix_enabled) {
		pci_disable_msix(pdev);
		vsoc_dev.msix_enabled = false;
	}
	kfree(vsoc_dev.msix_entries);
	vsoc_dev.msix_entries = NULL;
	vsoc_dev.regions = NULL;
	if (vsoc_dev.class_added) {
		class_destroy(vsoc_dev.class);
		vsoc_dev.class_added = false;
	}
	if (vsoc_dev.cdev_added) {
		cdev_del(&vsoc_dev.cdev);
		vsoc_dev.cdev_added = false;
	}
	if (vsoc_dev.major && vsoc_dev.layout) {
		unregister_chrdev_region(MKDEV(vsoc_dev.major, 0),
					 vsoc_dev.layout->region_count);
		vsoc_dev.major = 0;
	}
	vsoc_dev.layout = NULL;
	if (vsoc_dev.kernel_mapped_shm) {
		pci_iounmap(pdev, vsoc_dev.kernel_mapped_shm);
		vsoc_dev.kernel_mapped_shm = NULL;
	}
	if (vsoc_dev.regs) {
		pci_iounmap(pdev, vsoc_dev.regs);
		vsoc_dev.regs = NULL;
	}
	if (vsoc_dev.requested_regions) {
		pci_release_regions(pdev);
		vsoc_dev.requested_regions = false;
	}
	if (vsoc_dev.enabled_device) {
		pci_disable_device(pdev);
		vsoc_dev.enabled_device = false;
	}
	/* Do this last: it indicates that the device is not initialized. */
	vsoc_dev.dev = NULL;
}