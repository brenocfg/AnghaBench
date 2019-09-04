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
struct rpmsg_eptdev {int /*<<< orphan*/  dev; } ;
struct file {struct rpmsg_eptdev* private_data; } ;

/* Variables and functions */
 long EINVAL ; 
 unsigned int RPMSG_DESTROY_EPT_IOCTL ; 
 long rpmsg_eptdev_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long rpmsg_eptdev_ioctl(struct file *fp, unsigned int cmd,
			       unsigned long arg)
{
	struct rpmsg_eptdev *eptdev = fp->private_data;

	if (cmd != RPMSG_DESTROY_EPT_IOCTL)
		return -EINVAL;

	return rpmsg_eptdev_destroy(&eptdev->dev, NULL);
}