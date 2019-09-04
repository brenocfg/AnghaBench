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
struct rpmsg_ctrldev {int /*<<< orphan*/  dev; } ;
struct inode {int /*<<< orphan*/  i_cdev; } ;
struct file {struct rpmsg_ctrldev* private_data; } ;

/* Variables and functions */
 struct rpmsg_ctrldev* cdev_to_ctrldev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rpmsg_ctrldev_open(struct inode *inode, struct file *filp)
{
	struct rpmsg_ctrldev *ctrldev = cdev_to_ctrldev(inode->i_cdev);

	get_device(&ctrldev->dev);
	filp->private_data = ctrldev;

	return 0;
}