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
struct tsi721_bdma_chan {int active; int /*<<< orphan*/  tx_desc; int /*<<< orphan*/  free_list; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  bd_base; int /*<<< orphan*/  id; } ;
struct dma_chan {TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 struct tsi721_bdma_chan* to_tsi721_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  tsi721_bdma_ch_free (struct tsi721_bdma_chan*) ; 
 int /*<<< orphan*/  tsi721_bdma_interrupt_enable (struct tsi721_bdma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsi721_sync_dma_irq (struct tsi721_bdma_chan*) ; 
 int /*<<< orphan*/  tsi_debug (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tsi721_free_chan_resources(struct dma_chan *dchan)
{
	struct tsi721_bdma_chan *bdma_chan = to_tsi721_chan(dchan);

	tsi_debug(DMA, &dchan->dev->device, "DMAC%d", bdma_chan->id);

	if (!bdma_chan->bd_base)
		return;

	tsi721_bdma_interrupt_enable(bdma_chan, 0);
	bdma_chan->active = false;
	tsi721_sync_dma_irq(bdma_chan);
	tasklet_kill(&bdma_chan->tasklet);
	INIT_LIST_HEAD(&bdma_chan->free_list);
	kfree(bdma_chan->tx_desc);
	tsi721_bdma_ch_free(bdma_chan);
}