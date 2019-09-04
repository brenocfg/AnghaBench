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
struct virtio_device {int /*<<< orphan*/  dev; } ;
struct rproc_vdev {int rsc_offset; TYPE_1__* rproc; } ;
struct fw_rsc_vdev {size_t num_of_vrings; unsigned int config_len; int /*<<< orphan*/ * vring; } ;
struct TYPE_2__ {scalar_t__ table_ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,unsigned int) ; 
 struct rproc_vdev* vdev_to_rvdev (struct virtio_device*) ; 

__attribute__((used)) static void rproc_virtio_set(struct virtio_device *vdev, unsigned int offset,
			     const void *buf, unsigned int len)
{
	struct rproc_vdev *rvdev = vdev_to_rvdev(vdev);
	struct fw_rsc_vdev *rsc;
	void *cfg;

	rsc = (void *)rvdev->rproc->table_ptr + rvdev->rsc_offset;
	cfg = &rsc->vring[rsc->num_of_vrings];

	if (offset + len > rsc->config_len || offset + len < len) {
		dev_err(&vdev->dev, "rproc_virtio_set: access out of bounds\n");
		return;
	}

	memcpy(cfg + offset, buf, len);
}