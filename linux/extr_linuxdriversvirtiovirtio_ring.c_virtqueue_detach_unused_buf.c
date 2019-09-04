#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int num; TYPE_2__* avail; } ;
struct TYPE_7__ {unsigned int num_free; } ;
struct vring_virtqueue {TYPE_4__ vring; TYPE_3__ vq; int /*<<< orphan*/  avail_idx_shadow; TYPE_1__* desc_state; } ;
struct virtqueue {int /*<<< orphan*/  vdev; } ;
struct TYPE_6__ {int /*<<< orphan*/  idx; } ;
struct TYPE_5__ {void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  END_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  START_USE (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  cpu_to_virtio16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  detach_buf (struct vring_virtqueue*,unsigned int,int /*<<< orphan*/ *) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

void *virtqueue_detach_unused_buf(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);
	unsigned int i;
	void *buf;

	START_USE(vq);

	for (i = 0; i < vq->vring.num; i++) {
		if (!vq->desc_state[i].data)
			continue;
		/* detach_buf clears data, so grab it now. */
		buf = vq->desc_state[i].data;
		detach_buf(vq, i, NULL);
		vq->avail_idx_shadow--;
		vq->vring.avail->idx = cpu_to_virtio16(_vq->vdev, vq->avail_idx_shadow);
		END_USE(vq);
		return buf;
	}
	/* That should have freed everything. */
	BUG_ON(vq->vq.num_free != vq->vring.num);

	END_USE(vq);
	return NULL;
}