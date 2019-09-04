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
struct vfio_ccw_private {scalar_t__ state; int /*<<< orphan*/  avail; int /*<<< orphan*/ * mdev; } ;
struct mdev_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ VFIO_CCW_STATE_NOT_OPER ; 
 scalar_t__ VFIO_CCW_STATE_STANDBY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdev_parent_dev (struct mdev_device*) ; 
 int /*<<< orphan*/  vfio_ccw_mdev_reset (struct mdev_device*) ; 

__attribute__((used)) static int vfio_ccw_mdev_remove(struct mdev_device *mdev)
{
	struct vfio_ccw_private *private =
		dev_get_drvdata(mdev_parent_dev(mdev));

	if ((private->state != VFIO_CCW_STATE_NOT_OPER) &&
	    (private->state != VFIO_CCW_STATE_STANDBY)) {
		if (!vfio_ccw_mdev_reset(mdev))
			private->state = VFIO_CCW_STATE_STANDBY;
		/* The state will be NOT_OPER on error. */
	}

	private->mdev = NULL;
	atomic_inc(&private->avail);

	return 0;
}