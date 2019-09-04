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
struct TYPE_4__ {int /*<<< orphan*/  desc; } ;
struct TYPE_3__ {int /*<<< orphan*/  vdev; } ;
struct vring_virtqueue {int /*<<< orphan*/  queue_dma_addr; TYPE_2__ vring; int /*<<< orphan*/  queue_size_in_bytes; TYPE_1__ vq; scalar_t__ we_own_ring; } ;
struct virtqueue {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vring_virtqueue*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 
 int /*<<< orphan*/  vring_free_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vring_del_virtqueue(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	if (vq->we_own_ring) {
		vring_free_queue(vq->vq.vdev, vq->queue_size_in_bytes,
				 vq->vring.desc, vq->queue_dma_addr);
	}
	list_del(&_vq->list);
	kfree(vq);
}