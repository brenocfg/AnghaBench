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
struct xdpsock {unsigned int rx_npkts; TYPE_1__* umem; int /*<<< orphan*/  rx; } ;
struct xdp_desc {int /*<<< orphan*/  addr; int /*<<< orphan*/  len; } ;
struct TYPE_2__ {int /*<<< orphan*/  fq; } ;

/* Variables and functions */
 int BATCH_SIZE ; 
 int /*<<< orphan*/  hex_dump (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umem_fill_to_kernel_ex (int /*<<< orphan*/ *,struct xdp_desc*,unsigned int) ; 
 unsigned int xq_deq (int /*<<< orphan*/ *,struct xdp_desc*,int) ; 
 char* xq_get_data (struct xdpsock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx_drop(struct xdpsock *xsk)
{
	struct xdp_desc descs[BATCH_SIZE];
	unsigned int rcvd, i;

	rcvd = xq_deq(&xsk->rx, descs, BATCH_SIZE);
	if (!rcvd)
		return;

	for (i = 0; i < rcvd; i++) {
		char *pkt = xq_get_data(xsk, descs[i].addr);

		hex_dump(pkt, descs[i].len, descs[i].addr);
	}

	xsk->rx_npkts += rcvd;

	umem_fill_to_kernel_ex(&xsk->umem->fq, descs, rcvd);
}