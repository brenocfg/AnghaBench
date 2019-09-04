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
struct txdma_mailbox {int dummy; } ;
struct tx_ring_info {int pending; int mark_freq; scalar_t__ wrap_bit; scalar_t__ cons; scalar_t__ prod; scalar_t__ descr; int /*<<< orphan*/  descr_dma; scalar_t__ mbox; int /*<<< orphan*/  mbox_dma; } ;
struct niu {int /*<<< orphan*/  dev; int /*<<< orphan*/  device; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_2__ {scalar_t__ (* alloc_coherent ) (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_TX_RING_SIZE ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  niu_set_max_burst (struct niu*,struct tx_ring_info*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int niu_alloc_tx_ring_info(struct niu *np,
				  struct tx_ring_info *rp)
{
	BUILD_BUG_ON(sizeof(struct txdma_mailbox) != 64);

	rp->mbox = np->ops->alloc_coherent(np->device,
					   sizeof(struct txdma_mailbox),
					   &rp->mbox_dma, GFP_KERNEL);
	if (!rp->mbox)
		return -ENOMEM;
	if ((unsigned long)rp->mbox & (64UL - 1)) {
		netdev_err(np->dev, "Coherent alloc gives misaligned TXDMA mailbox %p\n",
			   rp->mbox);
		return -EINVAL;
	}

	rp->descr = np->ops->alloc_coherent(np->device,
					    MAX_TX_RING_SIZE * sizeof(__le64),
					    &rp->descr_dma, GFP_KERNEL);
	if (!rp->descr)
		return -ENOMEM;
	if ((unsigned long)rp->descr & (64UL - 1)) {
		netdev_err(np->dev, "Coherent alloc gives misaligned TXDMA descr table %p\n",
			   rp->descr);
		return -EINVAL;
	}

	rp->pending = MAX_TX_RING_SIZE;
	rp->prod = 0;
	rp->cons = 0;
	rp->wrap_bit = 0;

	/* XXX make these configurable... XXX */
	rp->mark_freq = rp->pending / 4;

	niu_set_max_burst(np, rp);

	return 0;
}