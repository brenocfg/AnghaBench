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
struct vhost_virtqueue {int /*<<< orphan*/  used; int /*<<< orphan*/  avail; int /*<<< orphan*/  desc; int /*<<< orphan*/  num; scalar_t__ iotlb; int /*<<< orphan*/  log_base; } ;

/* Variables and functions */
 int vq_access_ok (struct vhost_virtqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_log_access_ok (struct vhost_virtqueue*,int /*<<< orphan*/ ) ; 

bool vhost_vq_access_ok(struct vhost_virtqueue *vq)
{
	if (!vq_log_access_ok(vq, vq->log_base))
		return false;

	/* Access validation occurs at prefetch time with IOTLB */
	if (vq->iotlb)
		return true;

	return vq_access_ok(vq, vq->num, vq->desc, vq->avail, vq->used);
}