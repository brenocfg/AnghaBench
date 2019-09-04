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
struct cpdma_chan_stats {int dummy; } ;
struct cpdma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (struct cpdma_chan_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

int cpdma_chan_get_stats(struct cpdma_chan *chan,
			 struct cpdma_chan_stats *stats)
{
	unsigned long flags;
	if (!chan)
		return -EINVAL;
	spin_lock_irqsave(&chan->lock, flags);
	memcpy(stats, &chan->stats, sizeof(*stats));
	spin_unlock_irqrestore(&chan->lock, flags);
	return 0;
}