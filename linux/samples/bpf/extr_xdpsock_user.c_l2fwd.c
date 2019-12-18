#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct xsk_socket_info {unsigned int rx_npkts; unsigned int outstanding_tx; int /*<<< orphan*/  rx; int /*<<< orphan*/  tx; TYPE_1__* umem; } ;
struct pollfd {int dummy; } ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  addr; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/  fq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATCH_SIZE ; 
 int /*<<< orphan*/  complete_tx_l2fwd (struct xsk_socket_info*,struct pollfd*) ; 
 int /*<<< orphan*/  exit_with_error (int) ; 
 int /*<<< orphan*/  hex_dump (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kick_tx (struct xsk_socket_info*) ; 
 int /*<<< orphan*/  num_socks ; 
 int /*<<< orphan*/  opt_timeout ; 
 int poll (struct pollfd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_mac_addresses (char*) ; 
 unsigned int xsk_ring_cons__peek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  xsk_ring_cons__release (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_3__* xsk_ring_cons__rx_desc (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ xsk_ring_prod__needs_wakeup (int /*<<< orphan*/ *) ; 
 int xsk_ring_prod__reserve (int /*<<< orphan*/ *,unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  xsk_ring_prod__submit (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_2__* xsk_ring_prod__tx_desc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xsk_umem__add_offset_to_addr (int /*<<< orphan*/ ) ; 
 char* xsk_umem__get_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2fwd(struct xsk_socket_info *xsk, struct pollfd *fds)
{
	unsigned int rcvd, i;
	u32 idx_rx = 0, idx_tx = 0;
	int ret;

	complete_tx_l2fwd(xsk, fds);

	rcvd = xsk_ring_cons__peek(&xsk->rx, BATCH_SIZE, &idx_rx);
	if (!rcvd) {
		if (xsk_ring_prod__needs_wakeup(&xsk->umem->fq))
			ret = poll(fds, num_socks, opt_timeout);
		return;
	}

	ret = xsk_ring_prod__reserve(&xsk->tx, rcvd, &idx_tx);
	while (ret != rcvd) {
		if (ret < 0)
			exit_with_error(-ret);
		if (xsk_ring_prod__needs_wakeup(&xsk->tx))
			kick_tx(xsk);
		ret = xsk_ring_prod__reserve(&xsk->tx, rcvd, &idx_tx);
	}

	for (i = 0; i < rcvd; i++) {
		u64 addr = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx)->addr;
		u32 len = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx++)->len;
		u64 orig = addr;

		addr = xsk_umem__add_offset_to_addr(addr);
		char *pkt = xsk_umem__get_data(xsk->umem->buffer, addr);

		swap_mac_addresses(pkt);

		hex_dump(pkt, len, addr);
		xsk_ring_prod__tx_desc(&xsk->tx, idx_tx)->addr = orig;
		xsk_ring_prod__tx_desc(&xsk->tx, idx_tx++)->len = len;
	}

	xsk_ring_prod__submit(&xsk->tx, rcvd);
	xsk_ring_cons__release(&xsk->rx, rcvd);

	xsk->rx_npkts += rcvd;
	xsk->outstanding_tx += rcvd;
}