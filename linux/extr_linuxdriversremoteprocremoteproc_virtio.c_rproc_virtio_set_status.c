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
typedef  int /*<<< orphan*/  u8 ;
struct virtio_device {int /*<<< orphan*/  dev; } ;
struct rproc_vdev {int rsc_offset; TYPE_1__* rproc; } ;
struct fw_rsc_vdev {int /*<<< orphan*/  status; } ;
struct TYPE_2__ {scalar_t__ table_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct rproc_vdev* vdev_to_rvdev (struct virtio_device*) ; 

__attribute__((used)) static void rproc_virtio_set_status(struct virtio_device *vdev, u8 status)
{
	struct rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	struct fw_rsc_vdev *rsc;

	rsc = (void *)rvdev->rproc->table_ptr + rvdev->rsc_offset;

	rsc->status = status;
	dev_dbg(&vdev->dev, "status: %d\n", status);
}