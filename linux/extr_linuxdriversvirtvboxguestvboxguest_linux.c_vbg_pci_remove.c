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
struct vbg_dev {int /*<<< orphan*/  misc_device; int /*<<< orphan*/  misc_device_user; int /*<<< orphan*/  dev; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_host_features ; 
 int /*<<< orphan*/  dev_attr_host_version ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  misc_deregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_disable_device (struct pci_dev*) ; 
 struct vbg_dev* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  vbg_core_exit (struct vbg_dev*) ; 
 int /*<<< orphan*/ * vbg_gdev ; 
 int /*<<< orphan*/  vbg_gdev_mutex ; 

__attribute__((used)) static void vbg_pci_remove(struct pci_dev *pci)
{
	struct vbg_dev *gdev = pci_get_drvdata(pci);

	mutex_lock(&vbg_gdev_mutex);
	vbg_gdev = NULL;
	mutex_unlock(&vbg_gdev_mutex);

	device_remove_file(gdev->dev, &dev_attr_host_features);
	device_remove_file(gdev->dev, &dev_attr_host_version);
	misc_deregister(&gdev->misc_device_user);
	misc_deregister(&gdev->misc_device);
	vbg_core_exit(gdev);
	pci_disable_device(pci);
}