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
struct xdpsock {unsigned int tx_npkts; scalar_t__ outstanding_tx; TYPE_1__* umem; int /*<<< orphan*/  sfd; } ;
struct TYPE_2__ {int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int BATCH_SIZE ; 
 int /*<<< orphan*/  kick_tx (int /*<<< orphan*/ ) ; 
 unsigned int umem_complete_from_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static inline void complete_tx_only(struct xdpsock *xsk)
{
	u64 descs[BATCH_SIZE];
	unsigned int rcvd;

	if (!xsk->outstanding_tx)
		return;

	kick_tx(xsk->sfd);

	rcvd = umem_complete_from_kernel(&xsk->umem->cq, descs, BATCH_SIZE);
	if (rcvd > 0) {
		xsk->outstanding_tx -= rcvd;
		xsk->tx_npkts += rcvd;
	}
}