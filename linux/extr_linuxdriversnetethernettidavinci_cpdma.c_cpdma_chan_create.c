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
struct TYPE_2__ {scalar_t__ txcp; scalar_t__ txhdp; scalar_t__ rxfree; scalar_t__ rxcp; scalar_t__ rxhdp; } ;
struct cpdma_ctlr {scalar_t__ num_chan; int /*<<< orphan*/  lock; int /*<<< orphan*/  chan_num; struct cpdma_chan** channels; TYPE_1__ params; int /*<<< orphan*/  dev; } ;
struct cpdma_chan {int chan_num; int /*<<< orphan*/  lock; int /*<<< orphan*/  mask; int /*<<< orphan*/  dir; int /*<<< orphan*/  td; int /*<<< orphan*/  int_clear; int /*<<< orphan*/  int_set; scalar_t__ cp; scalar_t__ hdp; scalar_t__ rxfree; scalar_t__ weight; scalar_t__ rate; int /*<<< orphan*/  handler; int /*<<< orphan*/  state; struct cpdma_ctlr* ctlr; } ;
typedef  int /*<<< orphan*/  cpdma_handler_fn ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CPDMA_RXINTMASKCLEAR ; 
 int /*<<< orphan*/  CPDMA_RXINTMASKSET ; 
 int /*<<< orphan*/  CPDMA_RXTEARDOWN ; 
 int /*<<< orphan*/  CPDMA_STATE_IDLE ; 
 int /*<<< orphan*/  CPDMA_TXINTMASKCLEAR ; 
 int /*<<< orphan*/  CPDMA_TXINTMASKSET ; 
 int /*<<< orphan*/  CPDMA_TXTEARDOWN ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct cpdma_chan* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __chan_linear (int) ; 
 int /*<<< orphan*/  chan_linear (struct cpdma_chan*) ; 
 int /*<<< orphan*/  cpdma_chan_split_pool (struct cpdma_ctlr*) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct cpdma_chan*) ; 
 struct cpdma_chan* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ is_rx_chan (struct cpdma_chan*) ; 
 int rx_chan_num (int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int tx_chan_num (int) ; 

struct cpdma_chan *cpdma_chan_create(struct cpdma_ctlr *ctlr, int chan_num,
				     cpdma_handler_fn handler, int rx_type)
{
	int offset = chan_num * 4;
	struct cpdma_chan *chan;
	unsigned long flags;

	chan_num = rx_type ? rx_chan_num(chan_num) : tx_chan_num(chan_num);

	if (__chan_linear(chan_num) >= ctlr->num_chan)
		return ERR_PTR(-EINVAL);

	chan = devm_kzalloc(ctlr->dev, sizeof(*chan), GFP_KERNEL);
	if (!chan)
		return ERR_PTR(-ENOMEM);

	spin_lock_irqsave(&ctlr->lock, flags);
	if (ctlr->channels[chan_num]) {
		spin_unlock_irqrestore(&ctlr->lock, flags);
		devm_kfree(ctlr->dev, chan);
		return ERR_PTR(-EBUSY);
	}

	chan->ctlr	= ctlr;
	chan->state	= CPDMA_STATE_IDLE;
	chan->chan_num	= chan_num;
	chan->handler	= handler;
	chan->rate	= 0;
	chan->weight	= 0;

	if (is_rx_chan(chan)) {
		chan->hdp	= ctlr->params.rxhdp + offset;
		chan->cp	= ctlr->params.rxcp + offset;
		chan->rxfree	= ctlr->params.rxfree + offset;
		chan->int_set	= CPDMA_RXINTMASKSET;
		chan->int_clear	= CPDMA_RXINTMASKCLEAR;
		chan->td	= CPDMA_RXTEARDOWN;
		chan->dir	= DMA_FROM_DEVICE;
	} else {
		chan->hdp	= ctlr->params.txhdp + offset;
		chan->cp	= ctlr->params.txcp + offset;
		chan->int_set	= CPDMA_TXINTMASKSET;
		chan->int_clear	= CPDMA_TXINTMASKCLEAR;
		chan->td	= CPDMA_TXTEARDOWN;
		chan->dir	= DMA_TO_DEVICE;
	}
	chan->mask = BIT(chan_linear(chan));

	spin_lock_init(&chan->lock);

	ctlr->channels[chan_num] = chan;
	ctlr->chan_num++;

	cpdma_chan_split_pool(ctlr);

	spin_unlock_irqrestore(&ctlr->lock, flags);
	return chan;
}