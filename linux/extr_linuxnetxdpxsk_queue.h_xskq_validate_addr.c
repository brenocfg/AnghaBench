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
typedef  int u64 ;
struct TYPE_2__ {int chunk_mask; } ;
struct xsk_queue {unsigned int cons_tail; unsigned int cons_head; unsigned int ring_mask; TYPE_1__ umem_props; scalar_t__ ring; } ;
struct xdp_umem_ring {int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ xskq_is_valid_addr (struct xsk_queue*,int) ; 

__attribute__((used)) static inline u64 *xskq_validate_addr(struct xsk_queue *q, u64 *addr)
{
	while (q->cons_tail != q->cons_head) {
		struct xdp_umem_ring *ring = (struct xdp_umem_ring *)q->ring;
		unsigned int idx = q->cons_tail & q->ring_mask;

		*addr = READ_ONCE(ring->desc[idx]) & q->umem_props.chunk_mask;
		if (xskq_is_valid_addr(q, *addr))
			return addr;

		q->cons_tail++;
	}

	return NULL;
}