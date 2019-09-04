#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct rpmsg_channel_info {int dummy; } ;
struct device {int id; int /*<<< orphan*/  devt; int /*<<< orphan*/  release; int /*<<< orphan*/  groups; int /*<<< orphan*/ * parent; int /*<<< orphan*/  class; } ;
struct rpmsg_eptdev {TYPE_1__ cdev; int /*<<< orphan*/  readq; int /*<<< orphan*/  queue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  ept_lock; struct rpmsg_channel_info chinfo; struct rpmsg_device* rpdev; struct device dev; } ;
struct rpmsg_device {int dummy; } ;
struct rpmsg_ctrldev {int /*<<< orphan*/  dev; struct rpmsg_device* rpdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RPMSG_DEV_MAX ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int cdev_add (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct rpmsg_eptdev*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct rpmsg_eptdev*) ; 
 struct rpmsg_eptdev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  rpmsg_class ; 
 int /*<<< orphan*/  rpmsg_ept_ida ; 
 int /*<<< orphan*/  rpmsg_eptdev_fops ; 
 int /*<<< orphan*/  rpmsg_eptdev_groups ; 
 int /*<<< orphan*/  rpmsg_eptdev_release_device ; 
 int /*<<< orphan*/  rpmsg_major ; 
 int /*<<< orphan*/  rpmsg_minor_ida ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpmsg_eptdev_create(struct rpmsg_ctrldev *ctrldev,
			       struct rpmsg_channel_info chinfo)
{
	struct rpmsg_device *rpdev = ctrldev->rpdev;
	struct rpmsg_eptdev *eptdev;
	struct device *dev;
	int ret;

	eptdev = kzalloc(sizeof(*eptdev), GFP_KERNEL);
	if (!eptdev)
		return -ENOMEM;

	dev = &eptdev->dev;
	eptdev->rpdev = rpdev;
	eptdev->chinfo = chinfo;

	mutex_init(&eptdev->ept_lock);
	spin_lock_init(&eptdev->queue_lock);
	skb_queue_head_init(&eptdev->queue);
	init_waitqueue_head(&eptdev->readq);

	device_initialize(dev);
	dev->class = rpmsg_class;
	dev->parent = &ctrldev->dev;
	dev->groups = rpmsg_eptdev_groups;
	dev_set_drvdata(dev, eptdev);

	cdev_init(&eptdev->cdev, &rpmsg_eptdev_fops);
	eptdev->cdev.owner = THIS_MODULE;

	ret = ida_simple_get(&rpmsg_minor_ida, 0, RPMSG_DEV_MAX, GFP_KERNEL);
	if (ret < 0)
		goto free_eptdev;
	dev->devt = MKDEV(MAJOR(rpmsg_major), ret);

	ret = ida_simple_get(&rpmsg_ept_ida, 0, 0, GFP_KERNEL);
	if (ret < 0)
		goto free_minor_ida;
	dev->id = ret;
	dev_set_name(dev, "rpmsg%d", ret);

	ret = cdev_add(&eptdev->cdev, dev->devt, 1);
	if (ret)
		goto free_ept_ida;

	/* We can now rely on the release function for cleanup */
	dev->release = rpmsg_eptdev_release_device;

	ret = device_add(dev);
	if (ret) {
		dev_err(dev, "device_add failed: %d\n", ret);
		put_device(dev);
	}

	return ret;

free_ept_ida:
	ida_simple_remove(&rpmsg_ept_ida, dev->id);
free_minor_ida:
	ida_simple_remove(&rpmsg_minor_ida, MINOR(dev->devt));
free_eptdev:
	put_device(dev);
	kfree(eptdev);

	return ret;
}