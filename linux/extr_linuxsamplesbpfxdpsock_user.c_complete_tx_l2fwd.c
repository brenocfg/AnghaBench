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
struct xdpsock {int outstanding_tx; unsigned int tx_npkts; TYPE_1__* umem; int /*<<< orphan*/  sfd; } ;
struct TYPE_2__ {int /*<<< orphan*/  fq; int /*<<< orphan*/  cq; } ;

/* Variables and functions */
 int BATCH_SIZE ; 
 int /*<<< orphan*/  kick_tx (int /*<<< orphan*/ ) ; 
 unsigned int umem_complete_from_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  umem_fill_to_kernel (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline void complete_tx_l2fwd(struct xdpsock *xsk)
{
	u64 descs[BATCH_SIZE];
	unsigned int rcvd;
	size_t ndescs;

	if (!xsk->outstanding_tx)
		return;

	kick_tx(xsk->sfd);
	ndescs = (xsk->outstanding_tx > BATCH_SIZE) ? BATCH_SIZE :
		 xsk->outstanding_tx;

	/* re-add completed Tx buffers */
	rcvd = umem_complete_from_kernel(&xsk->umem->cq, descs, ndescs);
	if (rcvd > 0) {
		umem_fill_to_kernel(&xsk->umem->fq, descs, rcvd);
		xsk->outstanding_tx -= rcvd;
		xsk->tx_npkts += rcvd;
	}
}