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
typedef  int /*<<< orphan*/  u32 ;
struct xsk_queue {unsigned int ring_mask; int /*<<< orphan*/  prod_head; scalar_t__ ring; } ;
struct xdp_rxtx_ring {TYPE_1__* desc; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int ENOSPC ; 
 scalar_t__ xskq_nb_free (struct xsk_queue*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int xskq_produce_batch_desc(struct xsk_queue *q,
					  u64 addr, u32 len)
{
	struct xdp_rxtx_ring *ring = (struct xdp_rxtx_ring *)q->ring;
	unsigned int idx;

	if (xskq_nb_free(q, q->prod_head, 1) == 0)
		return -ENOSPC;

	/* A, matches D */
	idx = (q->prod_head++) & q->ring_mask;
	ring->desc[idx].addr = addr;
	ring->desc[idx].len = len;

	return 0;
}