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
struct cpdma_chan {int desc_num; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_chan_get_rx_buf_num(struct cpdma_chan *chan)
{
	unsigned long flags;
	int desc_num;

	spin_lock_irqsave(&chan->lock, flags);
	desc_num = chan->desc_num;
	spin_unlock_irqrestore(&chan->lock, flags);

	return desc_num;
}