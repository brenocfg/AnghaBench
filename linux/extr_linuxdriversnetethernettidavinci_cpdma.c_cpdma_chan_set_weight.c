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
struct cpdma_chan {int weight; int /*<<< orphan*/  lock; struct cpdma_ctlr* ctlr; } ;

/* Variables and functions */
 int cpdma_chan_split_pool (struct cpdma_ctlr*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_chan_set_weight(struct cpdma_chan *ch, int weight)
{
	struct cpdma_ctlr *ctlr = ch->ctlr;
	unsigned long flags, ch_flags;
	int ret;

	spin_lock_irqsave(&ctlr->lock, flags);
	spin_lock_irqsave(&ch->lock, ch_flags);
	if (ch->weight == weight) {
		spin_unlock_irqrestore(&ch->lock, ch_flags);
		spin_unlock_irqrestore(&ctlr->lock, flags);
		return 0;
	}
	ch->weight = weight;
	spin_unlock_irqrestore(&ch->lock, ch_flags);

	/* re-split pool using new channel weight */
	ret = cpdma_chan_split_pool(ctlr);
	spin_unlock_irqrestore(&ctlr->lock, flags);
	return ret;
}