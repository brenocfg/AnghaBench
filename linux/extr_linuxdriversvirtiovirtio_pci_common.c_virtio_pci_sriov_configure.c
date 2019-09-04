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
struct virtio_device {TYPE_1__* config; } ;
struct virtio_pci_device {struct virtio_device vdev; } ;
struct pci_dev {int dummy; } ;
struct TYPE_2__ {int (* get_status ) (struct virtio_device*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int VIRTIO_CONFIG_S_DRIVER_OK ; 
 int /*<<< orphan*/  VIRTIO_F_SR_IOV ; 
 int /*<<< orphan*/  __virtio_test_bit (struct virtio_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_disable_sriov (struct pci_dev*) ; 
 int pci_enable_sriov (struct pci_dev*,int) ; 
 struct virtio_pci_device* pci_get_drvdata (struct pci_dev*) ; 
 scalar_t__ pci_vfs_assigned (struct pci_dev*) ; 
 int stub1 (struct virtio_device*) ; 

__attribute__((used)) static int virtio_pci_sriov_configure(struct pci_dev *pci_dev, int num_vfs)
{
	struct virtio_pci_device *vp_dev = pci_get_drvdata(pci_dev);
	struct virtio_device *vdev = &vp_dev->vdev;
	int ret;

	if (!(vdev->config->get_status(vdev) & VIRTIO_CONFIG_S_DRIVER_OK))
		return -EBUSY;

	if (!__virtio_test_bit(vdev, VIRTIO_F_SR_IOV))
		return -EINVAL;

	if (pci_vfs_assigned(pci_dev))
		return -EPERM;

	if (num_vfs == 0) {
		pci_disable_sriov(pci_dev);
		return 0;
	}

	ret = pci_enable_sriov(pci_dev, num_vfs);
	if (ret < 0)
		return ret;

	return num_vfs;
}