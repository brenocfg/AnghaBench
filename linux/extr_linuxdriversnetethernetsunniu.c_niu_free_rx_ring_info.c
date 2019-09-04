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
struct rxdma_mailbox {int dummy; } ;
struct rx_ring_info {int /*<<< orphan*/ * rxhash; scalar_t__ rbr_index; scalar_t__ rbr_table_size; int /*<<< orphan*/ * rbr; int /*<<< orphan*/  rbr_dma; scalar_t__ rcr_index; scalar_t__ rcr_table_size; int /*<<< orphan*/ * rcr; int /*<<< orphan*/  rcr_dma; int /*<<< orphan*/ * mbox; int /*<<< orphan*/  mbox_dma; } ;
struct niu {int /*<<< orphan*/  device; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  __le64 ;
typedef  int /*<<< orphan*/  __le32 ;
struct TYPE_2__ {int /*<<< orphan*/  (* free_coherent ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int MAX_RBR_RING_SIZE ; 
 int MAX_RCR_RING_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  niu_rbr_free (struct niu*,struct rx_ring_info*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_free_rx_ring_info(struct niu *np, struct rx_ring_info *rp)
{
	if (rp->mbox) {
		np->ops->free_coherent(np->device,
				       sizeof(struct rxdma_mailbox),
				       rp->mbox, rp->mbox_dma);
		rp->mbox = NULL;
	}
	if (rp->rcr) {
		np->ops->free_coherent(np->device,
				       MAX_RCR_RING_SIZE * sizeof(__le64),
				       rp->rcr, rp->rcr_dma);
		rp->rcr = NULL;
		rp->rcr_table_size = 0;
		rp->rcr_index = 0;
	}
	if (rp->rbr) {
		niu_rbr_free(np, rp);

		np->ops->free_coherent(np->device,
				       MAX_RBR_RING_SIZE * sizeof(__le32),
				       rp->rbr, rp->rbr_dma);
		rp->rbr = NULL;
		rp->rbr_table_size = 0;
		rp->rbr_index = 0;
	}
	kfree(rp->rxhash);
	rp->rxhash = NULL;
}