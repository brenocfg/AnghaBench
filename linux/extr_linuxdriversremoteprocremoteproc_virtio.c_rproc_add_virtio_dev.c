#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  release; struct device* parent; } ;
struct TYPE_4__ {int device; } ;
struct virtio_device {TYPE_2__ dev; int /*<<< orphan*/ * config; TYPE_1__ id; } ;
struct rproc_vdev {int /*<<< orphan*/  refcount; struct virtio_device vdev; struct rproc* rproc; } ;
struct device {int dummy; } ;
struct rproc {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_2__*) ; 
 int register_virtio_device (struct virtio_device*) ; 
 int /*<<< orphan*/  rproc_virtio_config_ops ; 
 int /*<<< orphan*/  rproc_virtio_dev_release ; 

int rproc_add_virtio_dev(struct rproc_vdev *rvdev, int id)
{
	struct rproc *rproc = rvdev->rproc;
	struct device *dev = &rproc->dev;
	struct virtio_device *vdev = &rvdev->vdev;
	int ret;

	vdev->id.device	= id,
	vdev->config = &rproc_virtio_config_ops,
	vdev->dev.parent = dev;
	vdev->dev.release = rproc_virtio_dev_release;

	/*
	 * We're indirectly making a non-temporary copy of the rproc pointer
	 * here, because drivers probed with this vdev will indirectly
	 * access the wrapping rproc.
	 *
	 * Therefore we must increment the rproc refcount here, and decrement
	 * it _only_ when the vdev is released.
	 */
	get_device(&rproc->dev);

	/* Reference the vdev and vring allocations */
	kref_get(&rvdev->refcount);

	ret = register_virtio_device(vdev);
	if (ret) {
		put_device(&vdev->dev);
		dev_err(dev, "failed to register vdev: %d\n", ret);
		goto out;
	}

	dev_info(dev, "registered %s (type %d)\n", dev_name(&vdev->dev), id);

out:
	return ret;
}