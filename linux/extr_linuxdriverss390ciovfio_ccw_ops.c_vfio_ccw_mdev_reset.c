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
typedef  int /*<<< orphan*/  u32 ;
struct vfio_ccw_private {int /*<<< orphan*/  state; struct subchannel* sch; } ;
struct subchannel {int dummy; } ;
struct mdev_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_CCW_STATE_IDLE ; 
 int cio_enable_subchannel (struct subchannel*,int /*<<< orphan*/ ) ; 
 struct vfio_ccw_private* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdev_parent_dev (struct mdev_device*) ; 
 int vfio_ccw_sch_quiesce (struct subchannel*) ; 

__attribute__((used)) static int vfio_ccw_mdev_reset(struct mdev_device *mdev)
{
	struct vfio_ccw_private *private;
	struct subchannel *sch;
	int ret;

	private = dev_get_drvdata(mdev_parent_dev(mdev));
	sch = private->sch;
	/*
	 * TODO:
	 * In the cureent stage, some things like "no I/O running" and "no
	 * interrupt pending" are clear, but we are not sure what other state
	 * we need to care about.
	 * There are still a lot more instructions need to be handled. We
	 * should come back here later.
	 */
	ret = vfio_ccw_sch_quiesce(sch);
	if (ret)
		return ret;

	ret = cio_enable_subchannel(sch, (u32)(unsigned long)sch);
	if (!ret)
		private->state = VFIO_CCW_STATE_IDLE;

	return ret;
}