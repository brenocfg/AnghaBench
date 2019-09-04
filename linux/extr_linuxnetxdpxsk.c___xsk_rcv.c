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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct xdp_sock {int /*<<< orphan*/  rx_dropped; TYPE_1__* umem; int /*<<< orphan*/  rx; } ;
struct xdp_buff {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {scalar_t__ chunk_size_nohr; int /*<<< orphan*/  fq; scalar_t__ headroom; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  xdp_return_buff (struct xdp_buff*) ; 
 void* xdp_umem_get_data (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xskq_discard_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xskq_peek_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int xskq_produce_batch_desc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int __xsk_rcv(struct xdp_sock *xs, struct xdp_buff *xdp, u32 len)
{
	void *buffer;
	u64 addr;
	int err;

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
		xdp_return_buff(xdp);
		return 0;
	}

	xs->rx_dropped++;
	return err;
}