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
typedef  int u64 ;
struct rx_ring_info {int dummy; } ;
struct niu {int num_rx_rings; struct rx_ring_info* rx_rings; TYPE_1__* parent; } ;
struct TYPE_2__ {int rxdma_clock_divider; } ;

/* Variables and functions */
 int /*<<< orphan*/  RED_RAN_INIT ; 
 int RED_RAN_INIT_OPMODE ; 
 int RED_RAN_INIT_VAL ; 
 int /*<<< orphan*/  RX_DMA_CK_DIV ; 
 int jiffies_64 ; 
 int /*<<< orphan*/  niu_init_drr_weight (struct niu*) ; 
 int niu_init_hostinfo (struct niu*) ; 
 int niu_init_one_rx_channel (struct niu*,struct rx_ring_info*) ; 
 int /*<<< orphan*/  niu_init_rdc_groups (struct niu*) ; 
 int /*<<< orphan*/  niu_lock_parent (struct niu*,unsigned long) ; 
 int /*<<< orphan*/  niu_unlock_parent (struct niu*,unsigned long) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int niu_init_rx_channels(struct niu *np)
{
	unsigned long flags;
	u64 seed = jiffies_64;
	int err, i;

	niu_lock_parent(np, flags);
	nw64(RX_DMA_CK_DIV, np->parent->rxdma_clock_divider);
	nw64(RED_RAN_INIT, RED_RAN_INIT_OPMODE | (seed & RED_RAN_INIT_VAL));
	niu_unlock_parent(np, flags);

	/* XXX RXDMA 32bit mode? XXX */

	niu_init_rdc_groups(np);
	niu_init_drr_weight(np);

	err = niu_init_hostinfo(np);
	if (err)
		return err;

	for (i = 0; i < np->num_rx_rings; i++) {
		struct rx_ring_info *rp = &np->rx_rings[i];

		err = niu_init_one_rx_channel(np, rp);
		if (err)
			return err;
	}

	return 0;
}