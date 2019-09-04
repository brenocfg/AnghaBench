#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  release; int /*<<< orphan*/ * parent; } ;
struct TYPE_5__ {int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;
struct TYPE_7__ {TYPE_4__ dev; TYPE_1__ id; int /*<<< orphan*/ * config; } ;
struct virtio_ccw_device {struct virtio_ccw_device* config_block; struct virtio_ccw_device* status; TYPE_3__ vdev; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  lock; int /*<<< orphan*/  virtqueues; int /*<<< orphan*/  wait_q; struct ccw_device* cdev; int /*<<< orphan*/  is_thinint; } ;
struct TYPE_6__ {int /*<<< orphan*/  cu_model; int /*<<< orphan*/  cu_type; } ;
struct ccw_device {int /*<<< orphan*/  dev; TYPE_2__ id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct virtio_ccw_device*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  get_ccwdev_lock (struct ccw_device*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct virtio_ccw_device*) ; 
 void* kzalloc (int,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_4__*) ; 
 int register_virtio_device (TYPE_3__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  virtio_ccw_config_ops ; 
 int /*<<< orphan*/  virtio_ccw_release_dev ; 
 int virtio_ccw_set_transport_rev (struct virtio_ccw_device*) ; 
 int /*<<< orphan*/  virtio_ccw_use_airq ; 

__attribute__((used)) static int virtio_ccw_online(struct ccw_device *cdev)
{
	int ret;
	struct virtio_ccw_device *vcdev;
	unsigned long flags;

	vcdev = kzalloc(sizeof(*vcdev), GFP_KERNEL);
	if (!vcdev) {
		dev_warn(&cdev->dev, "Could not get memory for virtio\n");
		ret = -ENOMEM;
		goto out_free;
	}
	vcdev->config_block = kzalloc(sizeof(*vcdev->config_block),
				   GFP_DMA | GFP_KERNEL);
	if (!vcdev->config_block) {
		ret = -ENOMEM;
		goto out_free;
	}
	vcdev->status = kzalloc(sizeof(*vcdev->status), GFP_DMA | GFP_KERNEL);
	if (!vcdev->status) {
		ret = -ENOMEM;
		goto out_free;
	}

	vcdev->is_thinint = virtio_ccw_use_airq; /* at least try */

	vcdev->vdev.dev.parent = &cdev->dev;
	vcdev->vdev.dev.release = virtio_ccw_release_dev;
	vcdev->vdev.config = &virtio_ccw_config_ops;
	vcdev->cdev = cdev;
	init_waitqueue_head(&vcdev->wait_q);
	INIT_LIST_HEAD(&vcdev->virtqueues);
	spin_lock_init(&vcdev->lock);
	mutex_init(&vcdev->io_lock);

	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	dev_set_drvdata(&cdev->dev, vcdev);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	vcdev->vdev.id.vendor = cdev->id.cu_type;
	vcdev->vdev.id.device = cdev->id.cu_model;

	ret = virtio_ccw_set_transport_rev(vcdev);
	if (ret)
		goto out_free;

	ret = register_virtio_device(&vcdev->vdev);
	if (ret) {
		dev_warn(&cdev->dev, "Failed to register virtio device: %d\n",
			 ret);
		goto out_put;
	}
	return 0;
out_put:
	spin_lock_irqsave(get_ccwdev_lock(cdev), flags);
	dev_set_drvdata(&cdev->dev, NULL);
	spin_unlock_irqrestore(get_ccwdev_lock(cdev), flags);
	put_device(&vcdev->vdev.dev);
	return ret;
out_free:
	if (vcdev) {
		kfree(vcdev->status);
		kfree(vcdev->config_block);
	}
	kfree(vcdev);
	return ret;
}