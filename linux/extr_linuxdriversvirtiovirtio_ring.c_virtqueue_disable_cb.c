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
struct TYPE_4__ {TYPE_1__* avail; } ;
struct vring_virtqueue {int avail_flags_shadow; TYPE_2__ vring; int /*<<< orphan*/  event; } ;
struct virtqueue {int /*<<< orphan*/  vdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int VRING_AVAIL_F_NO_INTERRUPT ; 
 int /*<<< orphan*/  cpu_to_virtio16 (int /*<<< orphan*/ ,int) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

void virtqueue_disable_cb(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	if (!(vq->avail_flags_shadow & VRING_AVAIL_F_NO_INTERRUPT)) {
		vq->avail_flags_shadow |= VRING_AVAIL_F_NO_INTERRUPT;
		if (!vq->event)
			vq->vring.avail->flags = cpu_to_virtio16(_vq->vdev, vq->avail_flags_shadow);
	}

}