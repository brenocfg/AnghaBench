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
typedef  int /*<<< orphan*/  u8 ;
struct virtio_device {int dummy; } ;
struct virtio_ccw_device {int revision; int /*<<< orphan*/ * status; } ;
struct ccw1 {int count; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_READ_STATUS ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_CCW_DOING_READ_STATUS ; 
 int /*<<< orphan*/  ccw_io_helper (struct virtio_ccw_device*,struct ccw1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ccw1*) ; 
 struct ccw1* kzalloc (int,int) ; 
 struct virtio_ccw_device* to_vc_device (struct virtio_device*) ; 

__attribute__((used)) static u8 virtio_ccw_get_status(struct virtio_device *vdev)
{
	struct virtio_ccw_device *vcdev = to_vc_device(vdev);
	u8 old_status = *vcdev->status;
	struct ccw1 *ccw;

	if (vcdev->revision < 1)
		return *vcdev->status;

	ccw = kzalloc(sizeof(*ccw), GFP_DMA | GFP_KERNEL);
	if (!ccw)
		return old_status;

	ccw->cmd_code = CCW_CMD_READ_STATUS;
	ccw->flags = 0;
	ccw->count = sizeof(*vcdev->status);
	ccw->cda = (__u32)(unsigned long)vcdev->status;
	ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_READ_STATUS);
/*
 * If the channel program failed (should only happen if the device
 * was hotunplugged, and then we clean up via the machine check
 * handler anyway), vcdev->status was not overwritten and we just
 * return the old status, which is fine.
*/
	kfree(ccw);

	return *vcdev->status;
}