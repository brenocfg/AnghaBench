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
struct cpdma_ctlr {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; int /*<<< orphan*/  chan_num; int /*<<< orphan*/ ** channels; } ;
struct cpdma_chan {scalar_t__ state; size_t chan_num; struct cpdma_ctlr* ctlr; } ;

/* Variables and functions */
 scalar_t__ CPDMA_STATE_IDLE ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpdma_chan_split_pool (struct cpdma_ctlr*) ; 
 int /*<<< orphan*/  cpdma_chan_stop (struct cpdma_chan*) ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct cpdma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_chan_destroy(struct cpdma_chan *chan)
{
	struct cpdma_ctlr *ctlr;
	unsigned long flags;

	if (!chan)
		return -EINVAL;
	ctlr = chan->ctlr;

	spin_lock_irqsave(&ctlr->lock, flags);
	if (chan->state != CPDMA_STATE_IDLE)
		cpdma_chan_stop(chan);
	ctlr->channels[chan->chan_num] = NULL;
	ctlr->chan_num--;
	devm_kfree(ctlr->dev, chan);
	cpdma_chan_split_pool(ctlr);

	spin_unlock_irqrestore(&ctlr->lock, flags);
	return 0;
}