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
struct vfio_pci_device {int /*<<< orphan*/  pdev; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  driver_lock ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfio_pci_disable (struct vfio_pci_device*) ; 
 int /*<<< orphan*/  vfio_spapr_pci_eeh_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vfio_pci_release(void *device_data)
{
	struct vfio_pci_device *vdev = device_data;

	mutex_lock(&driver_lock);

	if (!(--vdev->refcnt)) {
		vfio_spapr_pci_eeh_release(vdev->pdev);
		vfio_pci_disable(vdev);
	}

	mutex_unlock(&driver_lock);

	module_put(THIS_MODULE);
}