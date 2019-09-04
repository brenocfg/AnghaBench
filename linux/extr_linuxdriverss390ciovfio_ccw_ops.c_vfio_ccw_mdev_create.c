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
struct vfio_ccw_private {scalar_t__ state; struct mdev_device* mdev; int /*<<< orphan*/  avail; } ;
struct mdev_device {int dummy; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int EPERM ; 
 scalar_t__ VFIO_CCW_STATE_IDLE ; 
 scalar_t__ VFIO_CCW_STATE_NOT_OPER ; 
 scalar_t__ atomic_dec_if_positive (int /*<<< orphan*/ *) ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdev_parent_dev (struct mdev_device*) ; 

__attribute__((used)) static int vfio_ccw_mdev_create(struct kobject *kobj, struct mdev_device *mdev)
{
	struct vfio_ccw_private *private =
		dev_get_drvdata(mdev_parent_dev(mdev));

	if (private->state == VFIO_CCW_STATE_NOT_OPER)
		return -ENODEV;

	if (atomic_dec_if_positive(&private->avail) < 0)
		return -EPERM;

	private->mdev = mdev;
	private->state = VFIO_CCW_STATE_IDLE;

	return 0;
}