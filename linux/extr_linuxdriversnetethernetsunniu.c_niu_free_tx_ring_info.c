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
struct txdma_mailbox {int dummy; } ;
struct tx_ring_info {scalar_t__ wrap_bit; scalar_t__ cons; scalar_t__ prod; scalar_t__ pending; int /*<<< orphan*/ * descr; int /*<<< orphan*/  descr_dma; TYPE_1__* tx_buffs; int /*<<< orphan*/ * mbox; int /*<<< orphan*/  mbox_dma; } ;
struct niu {int /*<<< orphan*/  device; TYPE_2__* ops; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_4__ {int /*<<< orphan*/  (* free_coherent ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {scalar_t__ skb; } ;

/* Variables and functions */
 int MAX_TX_RING_SIZE ; 
 int /*<<< orphan*/  release_tx_packet (struct niu*,struct tx_ring_info*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_free_tx_ring_info(struct niu *np, struct tx_ring_info *rp)
{
	if (rp->mbox) {
		np->ops->free_coherent(np->device,
				       sizeof(struct txdma_mailbox),
				       rp->mbox, rp->mbox_dma);
		rp->mbox = NULL;
	}
	if (rp->descr) {
		int i;

		for (i = 0; i < MAX_TX_RING_SIZE; i++) {
			if (rp->tx_buffs[i].skb)
				(void) release_tx_packet(np, rp, i);
		}

		np->ops->free_coherent(np->device,
				       MAX_TX_RING_SIZE * sizeof(__le64),
				       rp->descr, rp->descr_dma);
		rp->descr = NULL;
		rp->pending = 0;
		rp->prod = 0;
		rp->cons = 0;
		rp->wrap_bit = 0;
	}
}