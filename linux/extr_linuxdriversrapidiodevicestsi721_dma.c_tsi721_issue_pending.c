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
struct tsi721_bdma_chan {int /*<<< orphan*/  lock; scalar_t__ active; int /*<<< orphan*/  id; } ;
struct dma_chan {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tsi721_bdma_chan* to_tsi721_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  tsi721_advance_work (struct tsi721_bdma_chan*,int /*<<< orphan*/ *) ; 
 scalar_t__ tsi721_dma_is_idle (struct tsi721_bdma_chan*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi721_issue_pending(struct dma_chan *dchan)
{
	struct tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);

	tsi_debug(DMA, &dchan->dev->device, "DMAC%d", bdma_chan->id);

	spin_lock_bh(&bdma_chan->lock);
	if (tsi721_dma_is_idle(bdma_chan) && bdma_chan->active) {
		tsi721_advance_work(bdma_chan, NULL);
	}
	spin_unlock_bh(&bdma_chan->lock);
}