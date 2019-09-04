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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;
struct rpmsg_eptdev {struct rpmsg_endpoint* ept; TYPE_1__ chinfo; struct device dev; struct rpmsg_device* rpdev; } ;
struct rpmsg_endpoint {int dummy; } ;
struct rpmsg_device {int dummy; } ;
struct inode {int /*<<< orphan*/  i_cdev; } ;
struct file {struct rpmsg_eptdev* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rpmsg_eptdev* cdev_to_eptdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 struct rpmsg_endpoint* rpmsg_create_ept (struct rpmsg_device*,int /*<<< orphan*/ ,struct rpmsg_eptdev*,TYPE_1__) ; 
 int /*<<< orphan*/  rpmsg_ept_cb ; 

__attribute__((used)) static int rpmsg_eptdev_open(struct inode *inode, struct file *filp)
{
	struct rpmsg_eptdev *eptdev = cdev_to_eptdev(inode->i_cdev);
	struct rpmsg_endpoint *ept;
	struct rpmsg_device *rpdev = eptdev->rpdev;
	struct device *dev = &eptdev->dev;

	get_device(dev);

	ept = rpmsg_create_ept(rpdev, rpmsg_ept_cb, eptdev, eptdev->chinfo);
	if (!ept) {
		dev_err(dev, "failed to open %s\n", eptdev->chinfo.name);
		put_device(dev);
		return -EINVAL;
	}

	eptdev->ept = ept;
	filp->private_data = eptdev;

	return 0;
}