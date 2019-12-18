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
struct xsk_queue {scalar_t__ cons_tail; scalar_t__ cons_head; TYPE_1__* ring; } ;
struct xdp_umem {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  consumer; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_BATCH_SIZE ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_rmb () ; 
 scalar_t__ xskq_nb_avail (struct xsk_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xskq_validate_addr (struct xsk_queue*,int /*<<< orphan*/ *,struct xdp_umem*) ; 

__attribute__((used)) static inline u64 *xskq_peek_addr(struct xsk_queue *q, u64 *addr,
				  struct xdp_umem *umem)
{
	if (q->cons_tail == q->cons_head) {
		smp_mb(); /* D, matches A */
		WRITE_ONCE(q->ring->consumer, q->cons_tail);
		q->cons_head = q->cons_tail + xskq_nb_avail(q, RX_BATCH_SIZE);

		/* Order consumer and data */
		smp_rmb();
	}

	return xskq_validate_addr(q, addr, umem);
}