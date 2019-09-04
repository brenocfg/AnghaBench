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
struct cpdma_ctlr {scalar_t__ state; int /*<<< orphan*/  lock; scalar_t__* channels; } ;

/* Variables and functions */
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ CPDMA_STATE_ACTIVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpdma_chan_int_ctrl (scalar_t__,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_ctlr_int_ctrl(struct cpdma_ctlr *ctlr, bool enable)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&ctlr->lock, flags);
	if (ctlr->state != CPDMA_STATE_ACTIVE) {
		spin_unlock_irqrestore(&ctlr->lock, flags);
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(ctlr->channels); i++) {
		if (ctlr->channels[i])
			cpdma_chan_int_ctrl(ctlr->channels[i], enable);
	}

	spin_unlock_irqrestore(&ctlr->lock, flags);
	return 0;
}