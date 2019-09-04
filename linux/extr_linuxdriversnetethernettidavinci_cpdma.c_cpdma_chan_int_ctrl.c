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
struct cpdma_chan {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  mask; int /*<<< orphan*/  int_clear; int /*<<< orphan*/  int_set; int /*<<< orphan*/  ctlr; } ;

/* Variables and functions */
 scalar_t__ CPDMA_STATE_ACTIVE ; 
 int EINVAL ; 
 int /*<<< orphan*/  dma_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_chan_int_ctrl(struct cpdma_chan *chan, bool enable)
{
	unsigned long flags;

	spin_lock_irqsave(&chan->lock, flags);
	if (chan->state != CPDMA_STATE_ACTIVE) {
		spin_unlock_irqrestore(&chan->lock, flags);
		return -EINVAL;
	}

	dma_reg_write(chan->ctlr, enable ? chan->int_set : chan->int_clear,
		      chan->mask);
	spin_unlock_irqrestore(&chan->lock, flags);

	return 0;
}