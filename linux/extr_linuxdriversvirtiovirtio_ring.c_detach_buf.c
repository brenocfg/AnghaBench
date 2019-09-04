#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/  vdev; int /*<<< orphan*/  num_free; } ;
struct TYPE_4__ {struct vring_desc* desc; } ;
struct vring_virtqueue {unsigned int free_head; TYPE_3__* desc_state; TYPE_2__ vq; TYPE_1__ vring; scalar_t__ indirect; } ;
struct vring_desc {int flags; int next; int /*<<< orphan*/  len; } ;
typedef  int __virtio16 ;
struct TYPE_6__ {struct vring_desc* indir_desc; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int VRING_DESC_F_INDIRECT ; 
 unsigned int VRING_DESC_F_NEXT ; 
 int cpu_to_virtio16 (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  kfree (struct vring_desc*) ; 
 unsigned int virtio16_to_cpu (int /*<<< orphan*/ ,int) ; 
 int virtio32_to_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vring_unmap_one (struct vring_virtqueue*,struct vring_desc*) ; 

__attribute__((used)) static void detach_buf(struct vring_virtqueue *vq, unsigned int head,
		       void **ctx)
{
	unsigned int i, j;
	__virtio16 nextflag = cpu_to_virtio16(vq->vq.vdev, VRING_DESC_F_NEXT);

	/* Clear data ptr. */
	vq->desc_state[head].data = NULL;

	/* Put back on free list: unmap first-level descriptors and find end */
	i = head;

	while (vq->vring.desc[i].flags & nextflag) {
		vring_unmap_one(vq, &vq->vring.desc[i]);
		i = virtio16_to_cpu(vq->vq.vdev, vq->vring.desc[i].next);
		vq->vq.num_free++;
	}

	vring_unmap_one(vq, &vq->vring.desc[i]);
	vq->vring.desc[i].next = cpu_to_virtio16(vq->vq.vdev, vq->free_head);
	vq->free_head = head;

	/* Plus final descriptor */
	vq->vq.num_free++;

	if (vq->indirect) {
		struct vring_desc *indir_desc = vq->desc_state[head].indir_desc;
		u32 len;

		/* Free the indirect table, if any, now that it's unmapped. */
		if (!indir_desc)
			return;

		len = virtio32_to_cpu(vq->vq.vdev, vq->vring.desc[head].len);

		BUG_ON(!(vq->vring.desc[head].flags &
			 cpu_to_virtio16(vq->vq.vdev, VRING_DESC_F_INDIRECT)));
		BUG_ON(len == 0 || len % sizeof(struct vring_desc));

		for (j = 0; j < len / sizeof(struct vring_desc); j++)
			vring_unmap_one(vq, &indir_desc[j]);

		kfree(indir_desc);
		vq->desc_state[head].indir_desc = NULL;
	} else if (ctx) {
		*ctx = vq->desc_state[head].indir_desc;
	}
}