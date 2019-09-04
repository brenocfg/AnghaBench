#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct mx3fb_info {scalar_t__ cookie; TYPE_2__* txd; int /*<<< orphan*/ * sg; struct idmac_channel* idmac_channel; struct mx3fb_data* mx3fb; } ;
struct mx3fb_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct dma_chan {int /*<<< orphan*/  chan_id; } ;
struct idmac_channel {int /*<<< orphan*/  queue; struct dma_chan dma_chan; } ;
typedef  scalar_t__ dma_cookie_t ;
struct TYPE_6__ {scalar_t__ (* tx_submit ) (TYPE_2__*) ;int /*<<< orphan*/  callback; struct TYPE_6__* callback_param; } ;
struct TYPE_5__ {int /*<<< orphan*/  sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_MEM_TO_DEV ; 
 int /*<<< orphan*/  DMA_PREP_INTERRUPT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_async_issue_pending (struct dma_chan*) ; 
 TYPE_2__* dmaengine_prep_slave_sg (struct dma_chan*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mx3fb_dma_done ; 
 int /*<<< orphan*/  sdc_fb_init (struct mx3fb_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 
 TYPE_1__* to_tx_desc (TYPE_2__*) ; 

__attribute__((used)) static void sdc_enable_channel(struct mx3fb_info *mx3_fbi)
{
	struct mx3fb_data *mx3fb = mx3_fbi->mx3fb;
	struct idmac_channel *ichan = mx3_fbi->idmac_channel;
	struct dma_chan *dma_chan = &ichan->dma_chan;
	unsigned long flags;
	dma_cookie_t cookie;

	if (mx3_fbi->txd)
		dev_dbg(mx3fb->dev, "mx3fbi %p, desc %p, sg %p\n", mx3_fbi,
			to_tx_desc(mx3_fbi->txd), to_tx_desc(mx3_fbi->txd)->sg);
	else
		dev_dbg(mx3fb->dev, "mx3fbi %p, txd = NULL\n", mx3_fbi);

	/* This enables the channel */
	if (mx3_fbi->cookie < 0) {
		mx3_fbi->txd = dmaengine_prep_slave_sg(dma_chan,
		      &mx3_fbi->sg[0], 1, DMA_MEM_TO_DEV, DMA_PREP_INTERRUPT);
		if (!mx3_fbi->txd) {
			dev_err(mx3fb->dev, "Cannot allocate descriptor on %d\n",
				dma_chan->chan_id);
			return;
		}

		mx3_fbi->txd->callback_param	= mx3_fbi->txd;
		mx3_fbi->txd->callback		= mx3fb_dma_done;

		cookie = mx3_fbi->txd->tx_submit(mx3_fbi->txd);
		dev_dbg(mx3fb->dev, "%d: Submit %p #%d [%c]\n", __LINE__,
		       mx3_fbi->txd, cookie, list_empty(&ichan->queue) ? '-' : '+');
	} else {
		if (!mx3_fbi->txd || !mx3_fbi->txd->tx_submit) {
			dev_err(mx3fb->dev, "Cannot enable channel %d\n",
				dma_chan->chan_id);
			return;
		}

		/* Just re-activate the same buffer */
		dma_async_issue_pending(dma_chan);
		cookie = mx3_fbi->cookie;
		dev_dbg(mx3fb->dev, "%d: Re-submit %p #%d [%c]\n", __LINE__,
		       mx3_fbi->txd, cookie, list_empty(&ichan->queue) ? '-' : '+');
	}

	if (cookie >= 0) {
		spin_lock_irqsave(&mx3fb->lock, flags);
		sdc_fb_init(mx3_fbi);
		mx3_fbi->cookie = cookie;
		spin_unlock_irqrestore(&mx3fb->lock, flags);
	}

	/*
	 * Attention! Without this msleep the channel keeps generating
	 * interrupts. Next sdc_set_brightness() is going to be called
	 * from mx3fb_blank().
	 */
	msleep(2);
}