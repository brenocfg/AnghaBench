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
struct xsk_queue {unsigned int cons_tail; unsigned int cons_head; unsigned int ring_mask; scalar_t__ ring; } ;
struct xdp_umem {int dummy; } ;
struct xdp_rxtx_ring {int /*<<< orphan*/ * desc; } ;
struct xdp_desc {int dummy; } ;

/* Variables and functions */
 struct xdp_desc READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ xskq_is_valid_desc (struct xsk_queue*,struct xdp_desc*,struct xdp_umem*) ; 

__attribute__((used)) static inline struct xdp_desc *xskq_validate_desc(struct xsk_queue *q,
						  struct xdp_desc *desc,
						  struct xdp_umem *umem)
{
	while (q->cons_tail != q->cons_head) {
		struct xdp_rxtx_ring *ring = (struct xdp_rxtx_ring *)q->ring;
		unsigned int idx = q->cons_tail & q->ring_mask;

		*desc = READ_ONCE(ring->desc[idx]);
		if (xskq_is_valid_desc(q, desc, umem))
			return desc;

		q->cons_tail++;
	}

	return NULL;
}