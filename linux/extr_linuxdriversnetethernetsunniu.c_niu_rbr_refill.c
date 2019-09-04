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
struct rx_ring_info {int rbr_index; int rbr_pending; int rbr_blocks_per_page; int rbr_table_size; int rbr_kick_thresh; int /*<<< orphan*/  rx_channel; } ;
struct niu {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RBR_KICK (int /*<<< orphan*/ ) ; 
 int niu_rbr_add_page (struct niu*,struct rx_ring_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void niu_rbr_refill(struct niu *np, struct rx_ring_info *rp, gfp_t mask)
{
	int index = rp->rbr_index;

	rp->rbr_pending++;
	if ((rp->rbr_pending % rp->rbr_blocks_per_page) == 0) {
		int err = niu_rbr_add_page(np, rp, mask, index);

		if (unlikely(err)) {
			rp->rbr_pending--;
			return;
		}

		rp->rbr_index += rp->rbr_blocks_per_page;
		BUG_ON(rp->rbr_index > rp->rbr_table_size);
		if (rp->rbr_index == rp->rbr_table_size)
			rp->rbr_index = 0;

		if (rp->rbr_pending >= rp->rbr_kick_thresh) {
			nw64(RBR_KICK(rp->rx_channel), rp->rbr_pending);
			rp->rbr_pending = 0;
		}
	}
}