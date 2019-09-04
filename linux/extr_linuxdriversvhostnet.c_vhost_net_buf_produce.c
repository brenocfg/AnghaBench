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
struct vhost_net_buf {int tail; int /*<<< orphan*/  queue; scalar_t__ head; } ;
struct vhost_net_virtqueue {int /*<<< orphan*/  rx_ring; struct vhost_net_buf rxq; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHOST_NET_BATCH ; 
 int ptr_ring_consume_batched (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vhost_net_buf_produce(struct vhost_net_virtqueue *nvq)
{
	struct vhost_net_buf *rxq = &nvq->rxq;

	rxq->head = 0;
	rxq->tail = ptr_ring_consume_batched(nvq->rx_ring, rxq->queue,
					      VHOST_NET_BATCH);
	return rxq->tail;
}