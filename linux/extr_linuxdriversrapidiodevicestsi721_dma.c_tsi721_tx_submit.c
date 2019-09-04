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
struct tsi721_tx_desc {int /*<<< orphan*/  desc_node; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__* dev; } ;
struct tsi721_bdma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; int /*<<< orphan*/  active; int /*<<< orphan*/  id; TYPE_2__ dchan; } ;
struct dma_async_tx_descriptor {int /*<<< orphan*/  chan; } ;
typedef  int /*<<< orphan*/  dma_cookie_t ;
struct TYPE_3__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_IN_PROGRESS ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  dma_cookie_assign (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tsi721_bdma_chan* to_tsi721_chan (int /*<<< orphan*/ ) ; 
 struct tsi721_tx_desc* to_tsi721_desc (struct dma_async_tx_descriptor*) ; 
 int /*<<< orphan*/  tsi721_advance_work (struct tsi721_bdma_chan*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsi_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,struct dma_async_tx_descriptor*) ; 

__attribute__((used)) static dma_cookie_t tsi721_tx_submit(struct dma_async_tx_descriptor *txd)
{
	struct tsi721_tx_desc *desc = to_tsi721_desc(txd);
	struct tsi721_bdma_chan *bdma_chan = to_tsi721_chan(txd->chan);
	dma_cookie_t cookie;

	/* Check if the descriptor is detached from any lists */
	if (!list_empty(&desc->desc_node)) {
		tsi_err(&bdma_chan->dchan.dev->device,
			"DMAC%d wrong state of descriptor %p",
			bdma_chan->id, txd);
		return -EIO;
	}

	spin_lock_bh(&bdma_chan->lock);

	if (!bdma_chan->active) {
		spin_unlock_bh(&bdma_chan->lock);
		return -ENODEV;
	}

	cookie = dma_cookie_assign(txd);
	desc->status = DMA_IN_PROGRESS;
	list_add_tail(&desc->desc_node, &bdma_chan->queue);
	tsi721_advance_work(bdma_chan, NULL);

	spin_unlock_bh(&bdma_chan->lock);
	return cookie;
}