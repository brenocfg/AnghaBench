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
typedef  int /*<<< orphan*/  u64 ;
struct xsk_queue {size_t ring_mask; int /*<<< orphan*/  prod_head; scalar_t__ ring; } ;
struct xdp_umem_ring {int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  LAZY_UPDATE_THRESHOLD ; 
 scalar_t__ xskq_nb_free (struct xsk_queue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int xskq_produce_addr_lazy(struct xsk_queue *q, u64 addr)
{
	struct xdp_umem_ring *ring = (struct xdp_umem_ring *)q->ring;

	if (xskq_nb_free(q, q->prod_head, LAZY_UPDATE_THRESHOLD) == 0)
		return -ENOSPC;

	/* A, matches D */
	ring->desc[q->prod_head++ & q->ring_mask] = addr;
	return 0;
}