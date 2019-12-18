#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct xsk_socket_info {unsigned int rx_npkts; int /*<<< orphan*/  rx; TYPE_1__* umem; } ;
struct pollfd {int dummy; } ;
struct TYPE_4__ {scalar_t__ len; int /*<<< orphan*/  addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  fq; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATCH_SIZE ; 
 int /*<<< orphan*/  exit_with_error (int) ; 
 int /*<<< orphan*/  hex_dump (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  num_socks ; 
 int /*<<< orphan*/  opt_timeout ; 
 int poll (struct pollfd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int xsk_ring_cons__peek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  xsk_ring_cons__release (int /*<<< orphan*/ *,unsigned int) ; 
 TYPE_2__* xsk_ring_cons__rx_desc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * xsk_ring_prod__fill_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ xsk_ring_prod__needs_wakeup (int /*<<< orphan*/ *) ; 
 int xsk_ring_prod__reserve (int /*<<< orphan*/ *,unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  xsk_ring_prod__submit (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  xsk_umem__add_offset_to_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsk_umem__extract_addr (int /*<<< orphan*/ ) ; 
 char* xsk_umem__get_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_drop(struct xsk_socket_info *xsk, struct pollfd *fds)
{
	unsigned int rcvd, i;
	u32 idx_rx = 0, idx_fq = 0;
	int ret;

	rcvd = xsk_ring_cons__peek(&xsk->rx, BATCH_SIZE, &idx_rx);
	if (!rcvd) {
		if (xsk_ring_prod__needs_wakeup(&xsk->umem->fq))
			ret = poll(fds, num_socks, opt_timeout);
		return;
	}

	ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
	while (ret != rcvd) {
		if (ret < 0)
			exit_with_error(-ret);
		if (xsk_ring_prod__needs_wakeup(&xsk->umem->fq))
			ret = poll(fds, num_socks, opt_timeout);
		ret = xsk_ring_prod__reserve(&xsk->umem->fq, rcvd, &idx_fq);
	}

	for (i = 0; i < rcvd; i++) {
		u64 addr = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx)->addr;
		u32 len = xsk_ring_cons__rx_desc(&xsk->rx, idx_rx++)->len;
		u64 orig = xsk_umem__extract_addr(addr);

		addr = xsk_umem__add_offset_to_addr(addr);
		char *pkt = xsk_umem__get_data(xsk->umem->buffer, addr);

		hex_dump(pkt, len, addr);
		*xsk_ring_prod__fill_addr(&xsk->umem->fq, idx_fq++) = orig;
	}

	xsk_ring_prod__submit(&xsk->umem->fq, rcvd);
	xsk_ring_cons__release(&xsk->rx, rcvd);
	xsk->rx_npkts += rcvd;
}