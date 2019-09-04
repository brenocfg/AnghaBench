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
struct scc_channel {int /*<<< orphan*/  lock; int /*<<< orphan*/  tx_queue; int /*<<< orphan*/ * tx_buff; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void scc_discard_buffers(struct scc_channel *scc)
{
	unsigned long flags;
	
	spin_lock_irqsave(&scc->lock, flags);	
	if (scc->tx_buff != NULL)
	{
		dev_kfree_skb(scc->tx_buff);
		scc->tx_buff = NULL;
	}
	
	while (!skb_queue_empty(&scc->tx_queue))
		dev_kfree_skb(skb_dequeue(&scc->tx_queue));

	spin_unlock_irqrestore(&scc->lock, flags);
}