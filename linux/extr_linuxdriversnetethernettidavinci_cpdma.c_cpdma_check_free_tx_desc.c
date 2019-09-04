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
struct cpdma_desc_pool {int /*<<< orphan*/  gen_pool; } ;
struct cpdma_ctlr {struct cpdma_desc_pool* pool; } ;
struct cpdma_chan {scalar_t__ count; scalar_t__ desc_num; int /*<<< orphan*/  lock; struct cpdma_ctlr* ctlr; } ;

/* Variables and functions */
 scalar_t__ gen_pool_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

bool cpdma_check_free_tx_desc(struct cpdma_chan *chan)
{
	struct cpdma_ctlr	*ctlr = chan->ctlr;
	struct cpdma_desc_pool	*pool = ctlr->pool;
	bool			free_tx_desc;
	unsigned long		flags;

	spin_lock_irqsave(&chan->lock, flags);
	free_tx_desc = (chan->count < chan->desc_num) &&
			 gen_pool_avail(pool->gen_pool);
	spin_unlock_irqrestore(&chan->lock, flags);
	return free_tx_desc;
}