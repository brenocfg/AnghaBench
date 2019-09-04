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
struct vring_virtqueue {int /*<<< orphan*/  queue_dma_addr; int /*<<< orphan*/  we_own_ring; } ;
struct virtqueue {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct vring_virtqueue* to_vvq (struct virtqueue*) ; 

dma_addr_t virtqueue_get_desc_addr(struct virtqueue *_vq)
{
	struct vring_virtqueue *vq = to_vvq(_vq);

	BUG_ON(!vq->we_own_ring);

	return vq->queue_dma_addr;
}