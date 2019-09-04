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
struct rpmsg_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
struct device {int id; int /*<<< orphan*/  devt; int /*<<< orphan*/  release; int /*<<< orphan*/  class; int /*<<< orphan*/ * parent; } ;
struct rpmsg_ctrldev {TYPE_1__ cdev; struct device dev; struct rpmsg_device* rpdev; } ;

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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct rpmsg_ctrldev*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct rpmsg_ctrldev*) ; 
 struct rpmsg_ctrldev* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  rpmsg_class ; 
 int /*<<< orphan*/  rpmsg_ctrl_ida ; 
 int /*<<< orphan*/  rpmsg_ctrldev_fops ; 
 int /*<<< orphan*/  rpmsg_ctrldev_release_device ; 
 int /*<<< orphan*/  rpmsg_major ; 
 int /*<<< orphan*/  rpmsg_minor_ida ; 

__attribute__((used)) static int rpmsg_chrdev_probe(struct rpmsg_device *rpdev)
{
	struct rpmsg_ctrldev *ctrldev;
	struct device *dev;
	int ret;

	ctrldev = kzalloc(sizeof(*ctrldev), GFP_KERNEL);
	if (!ctrldev)
		return -ENOMEM;

	ctrldev->rpdev = rpdev;

	dev = &ctrldev->dev;
	device_initialize(dev);
	dev->parent = &rpdev->dev;
	dev->class = rpmsg_class;

	cdev_init(&ctrldev->cdev, &rpmsg_ctrldev_fops);
	ctrldev->cdev.owner = THIS_MODULE;

	ret = ida_simple_get(&rpmsg_minor_ida, 0, RPMSG_DEV_MAX, GFP_KERNEL);
	if (ret < 0)
		goto free_ctrldev;
	dev->devt = MKDEV(MAJOR(rpmsg_major), ret);

	ret = ida_simple_get(&rpmsg_ctrl_ida, 0, 0, GFP_KERNEL);
	if (ret < 0)
		goto free_minor_ida;
	dev->id = ret;
	dev_set_name(&ctrldev->dev, "rpmsg_ctrl%d", ret);

	ret = cdev_add(&ctrldev->cdev, dev->devt, 1);
	if (ret)
		goto free_ctrl_ida;

	/* We can now rely on the release function for cleanup */
	dev->release = rpmsg_ctrldev_release_device;

	ret = device_add(dev);
	if (ret) {
		dev_err(&rpdev->dev, "device_add failed: %d\n", ret);
		put_device(dev);
	}

	dev_set_drvdata(&rpdev->dev, ctrldev);

	return ret;

free_ctrl_ida:
	ida_simple_remove(&rpmsg_ctrl_ida, dev->id);
free_minor_ida:
	ida_simple_remove(&rpmsg_minor_ida, MINOR(dev->devt));
free_ctrldev:
	put_device(dev);
	kfree(ctrldev);

	return ret;
}