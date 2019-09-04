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
typedef  void* u8 ;
struct virtio_device {int dummy; } ;
struct virtio_ccw_device {void** status; } ;
struct ccw1 {int count; scalar_t__ cda; scalar_t__ flags; int /*<<< orphan*/  cmd_code; } ;
typedef  int /*<<< orphan*/  status ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCW_CMD_WRITE_STATUS ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_CCW_DOING_WRITE_STATUS ; 
 int ccw_io_helper (struct virtio_ccw_device*,struct ccw1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ccw1*) ; 
 struct ccw1* kzalloc (int,int) ; 
 struct virtio_ccw_device* to_vc_device (struct virtio_device*) ; 

__attribute__((used)) static void virtio_ccw_set_status(struct virtio_device *vdev, u8 status)
{
	struct virtio_ccw_device *vcdev = to_vc_device(vdev);
	u8 old_status = *vcdev->status;
	struct ccw1 *ccw;
	int ret;

	ccw = kzalloc(sizeof(*ccw), GFP_DMA | GFP_KERNEL);
	if (!ccw)
		return;

	/* Write the status to the host. */
	*vcdev->status = status;
	ccw->cmd_code = CCW_CMD_WRITE_STATUS;
	ccw->flags = 0;
	ccw->count = sizeof(status);
	ccw->cda = (__u32)(unsigned long)vcdev->status;
	ret = ccw_io_helper(vcdev, ccw, VIRTIO_CCW_DOING_WRITE_STATUS);
	/* Write failed? We assume status is unchanged. */
	if (ret)
		*vcdev->status = old_status;
	kfree(ccw);
}