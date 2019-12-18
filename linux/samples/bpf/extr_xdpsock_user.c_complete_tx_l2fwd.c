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
typedef  scalar_t__ u32 ;
struct xsk_umem_info {int /*<<< orphan*/  cq; int /*<<< orphan*/  fq; } ;
struct xsk_socket_info {size_t outstanding_tx; unsigned int tx_npkts; struct xsk_umem_info* umem; int /*<<< orphan*/  tx; } ;
struct pollfd {int dummy; } ;

/* Variables and functions */
 size_t BATCH_SIZE ; 
 int /*<<< orphan*/  exit_with_error (int) ; 
 int /*<<< orphan*/  kick_tx (struct xsk_socket_info*) ; 
 int /*<<< orphan*/  num_socks ; 
 int /*<<< orphan*/  opt_need_wakeup ; 
 int /*<<< orphan*/  opt_timeout ; 
 int poll (struct pollfd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xsk_ring_cons__comp_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int xsk_ring_cons__peek (int /*<<< orphan*/ *,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  xsk_ring_cons__release (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/ * xsk_ring_prod__fill_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xsk_ring_prod__needs_wakeup (int /*<<< orphan*/ *) ; 
 int xsk_ring_prod__reserve (int /*<<< orphan*/ *,unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  xsk_ring_prod__submit (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static inline void complete_tx_l2fwd(struct xsk_socket_info *xsk,
				     struct pollfd *fds)
{
	struct xsk_umem_info *umem = xsk->umem;
	u32 idx_cq = 0, idx_fq = 0;
	unsigned int rcvd;
	size_t ndescs;

	if (!xsk->outstanding_tx)
		return;

	if (!opt_need_wakeup || xsk_ring_prod__needs_wakeup(&xsk->tx))
		kick_tx(xsk);

	ndescs = (xsk->outstanding_tx > BATCH_SIZE) ? BATCH_SIZE :
		xsk->outstanding_tx;

	/* re-add completed Tx buffers */
	rcvd = xsk_ring_cons__peek(&umem->cq, ndescs, &idx_cq);
	if (rcvd > 0) {
		unsigned int i;
		int ret;

		ret = xsk_ring_prod__reserve(&umem->fq, rcvd, &idx_fq);
		while (ret != rcvd) {
			if (ret < 0)
				exit_with_error(-ret);
			if (xsk_ring_prod__needs_wakeup(&umem->fq))
				ret = poll(fds, num_socks, opt_timeout);
			ret = xsk_ring_prod__reserve(&umem->fq, rcvd, &idx_fq);
		}

		for (i = 0; i < rcvd; i++)
			*xsk_ring_prod__fill_addr(&umem->fq, idx_fq++) =
				*xsk_ring_cons__comp_addr(&umem->cq, idx_cq++);

		xsk_ring_prod__submit(&xsk->umem->fq, rcvd);
		xsk_ring_cons__release(&xsk->umem->cq, rcvd);
		xsk->outstanding_tx -= rcvd;
		xsk->tx_npkts += rcvd;
	}
}