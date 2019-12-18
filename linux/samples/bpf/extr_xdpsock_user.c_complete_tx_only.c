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
typedef  int /*<<< orphan*/  u32 ;
struct xsk_socket_info {unsigned int tx_npkts; scalar_t__ outstanding_tx; TYPE_1__* umem; int /*<<< orphan*/  tx; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATCH_SIZE ; 
 int /*<<< orphan*/  kick_tx (struct xsk_socket_info*) ; 
 int /*<<< orphan*/  opt_need_wakeup ; 
 unsigned int xsk_ring_cons__peek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xsk_ring_cons__release (int /*<<< orphan*/ *,unsigned int) ; 
 scalar_t__ xsk_ring_prod__needs_wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void complete_tx_only(struct xsk_socket_info *xsk)
{
	unsigned int rcvd;
	u32 idx;

	if (!xsk->outstanding_tx)
		return;

	if (!opt_need_wakeup || xsk_ring_prod__needs_wakeup(&xsk->tx))
		kick_tx(xsk);

	rcvd = xsk_ring_cons__peek(&xsk->umem->cq, BATCH_SIZE, &idx);
	if (rcvd > 0) {
		xsk_ring_cons__release(&xsk->umem->cq, rcvd);
		xsk->outstanding_tx -= rcvd;
		xsk->tx_npkts += rcvd;
	}
}