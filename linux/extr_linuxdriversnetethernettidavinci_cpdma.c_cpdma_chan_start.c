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
struct cpdma_ctlr {int /*<<< orphan*/  lock; } ;
struct cpdma_chan {struct cpdma_ctlr* ctlr; } ;

/* Variables and functions */
 int cpdma_chan_on (struct cpdma_chan*) ; 
 int cpdma_chan_set_chan_shaper (struct cpdma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_chan_start(struct cpdma_chan *chan)
{
	struct cpdma_ctlr *ctlr = chan->ctlr;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&ctlr->lock, flags);
	ret = cpdma_chan_set_chan_shaper(chan);
	spin_unlock_irqrestore(&ctlr->lock, flags);
	if (ret)
		return ret;

	ret = cpdma_chan_on(chan);
	if (ret)
		return ret;

	return 0;
}