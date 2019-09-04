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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct xdp_sock {scalar_t__ dev; scalar_t__ queue_id; int /*<<< orphan*/  rx_dropped; TYPE_2__* umem; int /*<<< orphan*/  rx; } ;
struct xdp_buff {scalar_t__ data_end; scalar_t__ data; TYPE_1__* rxq; } ;
struct TYPE_4__ {scalar_t__ chunk_size_nohr; int /*<<< orphan*/  fq; scalar_t__ headroom; } ;
struct TYPE_3__ {scalar_t__ dev; scalar_t__ queue_index; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 void* xdp_umem_get_data (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_flush (struct xdp_sock*) ; 
 int /*<<< orphan*/  xskq_discard_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xskq_peek_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xskq_produce_batch_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

int xsk_generic_rcv(struct xdp_sock *xs, struct xdp_buff *xdp)
{
	u32 len = xdp->data_end - xdp->data;
	void *buffer;
	u64 addr;
	int err;

	if (xs->dev != xdp->rxq->dev || xs->queue_id != xdp->rxq->queue_index)
		return -EINVAL;

	if (!xskq_peek_addr(xs->umem->fq, &addr) ||
	    len > xs->umem->chunk_size_nohr) {
		xs->rx_dropped++;
		return -ENOSPC;
	}

	addr += xs->umem->headroom;

	buffer = xdp_umem_get_data(xs->umem, addr);
	memcpy(buffer, xdp->data, len);
	err = xskq_produce_batch_desc(xs->rx, addr, len);
	if (!err) {
		xskq_discard_addr(xs->umem->fq);
		xsk_flush(xs);
		return 0;
	}

	xs->rx_dropped++;
	return err;
}