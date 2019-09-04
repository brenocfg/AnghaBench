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
 int /*<<< orphan*/  CPDMA_RXCONTROL ; 
 int /*<<< orphan*/  CPDMA_RXINTMASKCLEAR ; 
 scalar_t__ CPDMA_STATE_ACTIVE ; 
 scalar_t__ CPDMA_STATE_IDLE ; 
 scalar_t__ CPDMA_STATE_TEARDOWN ; 
 int /*<<< orphan*/  CPDMA_TXCONTROL ; 
 int /*<<< orphan*/  CPDMA_TXINTMASKCLEAR ; 
 int EINVAL ; 
 int /*<<< orphan*/  cpdma_chan_stop (scalar_t__) ; 
 int /*<<< orphan*/  dma_reg_write (struct cpdma_ctlr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_ctlr_stop(struct cpdma_ctlr *ctlr)
{
	unsigned long flags;
	int i;

	spin_lock_irqsave(&ctlr->lock, flags);
	if (ctlr->state != CPDMA_STATE_ACTIVE) {
		spin_unlock_irqrestore(&ctlr->lock, flags);
		return -EINVAL;
	}

	ctlr->state = CPDMA_STATE_TEARDOWN;
	spin_unlock_irqrestore(&ctlr->lock, flags);

	for (i = 0; i < ARRAY_SIZE(ctlr->channels); i++) {
		if (ctlr->channels[i])
			cpdma_chan_stop(ctlr->channels[i]);
	}

	spin_lock_irqsave(&ctlr->lock, flags);
	dma_reg_write(ctlr, CPDMA_RXINTMASKCLEAR, 0xffffffff);
	dma_reg_write(ctlr, CPDMA_TXINTMASKCLEAR, 0xffffffff);

	dma_reg_write(ctlr, CPDMA_TXCONTROL, 0);
	dma_reg_write(ctlr, CPDMA_RXCONTROL, 0);

	ctlr->state = CPDMA_STATE_IDLE;

	spin_unlock_irqrestore(&ctlr->lock, flags);
	return 0;
}