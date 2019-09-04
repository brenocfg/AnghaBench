#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct virtqueue {void (* callback ) (struct virtqueue*) ;char const* name; int num_free; unsigned int index; int /*<<< orphan*/  list; struct virtio_device* vdev; } ;
struct vring {int num; TYPE_2__* desc; TYPE_1__* avail; } ;
struct vring_virtqueue {int we_own_ring; int (* notify ) (struct virtqueue*) ;int weak_barriers; int broken; unsigned int avail_flags_shadow; int indirect; struct virtqueue vq; int /*<<< orphan*/  desc_state; struct vring vring; scalar_t__ free_head; scalar_t__ event; scalar_t__ num_added; scalar_t__ avail_idx_shadow; scalar_t__ last_used_idx; scalar_t__ queue_size_in_bytes; scalar_t__ queue_dma_addr; } ;
struct vring_desc_state {int dummy; } ;
struct virtio_device {int /*<<< orphan*/  vqs; } ;
struct TYPE_4__ {void* next; } ;
struct TYPE_3__ {void* flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VIRTIO_RING_F_EVENT_IDX ; 
 int /*<<< orphan*/  VIRTIO_RING_F_INDIRECT_DESC ; 
 unsigned int VRING_AVAIL_F_NO_INTERRUPT ; 
 void* cpu_to_virtio16 (struct virtio_device*,unsigned int) ; 
 struct vring_virtqueue* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ virtio_has_feature (struct virtio_device*,int /*<<< orphan*/ ) ; 

struct virtqueue *__vring_new_virtqueue(unsigned int index,
					struct vring vring,
					struct virtio_device *vdev,
					bool weak_barriers,
					bool context,
					bool (*notify)(struct virtqueue *),
					void (*callback)(struct virtqueue *),
					const char *name)
{
	unsigned int i;
	struct vring_virtqueue *vq;

	vq = kmalloc(sizeof(*vq) + vring.num * sizeof(struct vring_desc_state),
		     GFP_KERNEL);
	if (!vq)
		return NULL;

	vq->vring = vring;
	vq->vq.callback = callback;
	vq->vq.vdev = vdev;
	vq->vq.name = name;
	vq->vq.num_free = vring.num;
	vq->vq.index = index;
	vq->we_own_ring = false;
	vq->queue_dma_addr = 0;
	vq->queue_size_in_bytes = 0;
	vq->notify = notify;
	vq->weak_barriers = weak_barriers;
	vq->broken = false;
	vq->last_used_idx = 0;
	vq->avail_flags_shadow = 0;
	vq->avail_idx_shadow = 0;
	vq->num_added = 0;
	list_add_tail(&vq->vq.list, &vdev->vqs);
#ifdef DEBUG
	vq->in_use = false;
	vq->last_add_time_valid = false;
#endif

	vq->indirect = virtio_has_feature(vdev, VIRTIO_RING_F_INDIRECT_DESC) &&
		!context;
	vq->event = virtio_has_feature(vdev, VIRTIO_RING_F_EVENT_IDX);

	/* No callback?  Tell other side not to bother us. */
	if (!callback) {
		vq->avail_flags_shadow |= VRING_AVAIL_F_NO_INTERRUPT;
		if (!vq->event)
			vq->vring.avail->flags = cpu_to_virtio16(vdev, vq->avail_flags_shadow);
	}

	/* Put everything in free lists. */
	vq->free_head = 0;
	for (i = 0; i < vring.num-1; i++)
		vq->vring.desc[i].next = cpu_to_virtio16(vdev, i + 1);
	memset(vq->desc_state, 0, vring.num * sizeof(struct vring_desc_state));

	return &vq->vq;
}