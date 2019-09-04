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
struct xdpsock {unsigned int rx_npkts; unsigned int outstanding_tx; int /*<<< orphan*/  tx; int /*<<< orphan*/  rx; } ;
struct xdp_desc {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int BATCH_SIZE ; 
 int /*<<< orphan*/  complete_tx_l2fwd (struct xdpsock*) ; 
 int /*<<< orphan*/  hex_dump (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lassert (int) ; 
 int /*<<< orphan*/  swap_mac_addresses (char*) ; 
 unsigned int xq_deq (int /*<<< orphan*/ *,struct xdp_desc*,int) ; 
 int xq_enq (int /*<<< orphan*/ *,struct xdp_desc*,unsigned int) ; 
 char* xq_get_data (struct xdpsock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void l2fwd(struct xdpsock *xsk)
{
	for (;;) {
		struct xdp_desc descs[BATCH_SIZE];
		unsigned int rcvd, i;
		int ret;

		for (;;) {
			complete_tx_l2fwd(xsk);

			rcvd = xq_deq(&xsk->rx, descs, BATCH_SIZE);
			if (rcvd > 0)
				break;
		}

		for (i = 0; i < rcvd; i++) {
			char *pkt = xq_get_data(xsk, descs[i].addr);

			swap_mac_addresses(pkt);

			hex_dump(pkt, descs[i].len, descs[i].addr);
		}

		xsk->rx_npkts += rcvd;

		ret = xq_enq(&xsk->tx, descs, rcvd);
		lassert(ret == 0);
		xsk->outstanding_tx += rcvd;
	}
}