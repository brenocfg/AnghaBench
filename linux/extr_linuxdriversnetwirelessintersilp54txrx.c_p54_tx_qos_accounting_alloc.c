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
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct p54_tx_queue_stats {scalar_t__ len; scalar_t__ limit; int /*<<< orphan*/  count; } ;
struct p54_common {int /*<<< orphan*/  tx_stats_lock; int /*<<< orphan*/  hw; struct p54_tx_queue_stats* tx_stats; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 scalar_t__ IS_QOS_QUEUE (size_t const) ; 
 size_t P54_QUEUE_DATA ; 
 size_t const P54_QUEUE_NUM ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ieee80211_stop_queue (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int p54_tx_qos_accounting_alloc(struct p54_common *priv,
				       struct sk_buff *skb,
				       const u16 p54_queue)
{
	struct p54_tx_queue_stats *queue;
	unsigned long flags;

	if (WARN_ON(p54_queue >= P54_QUEUE_NUM))
		return -EINVAL;

	queue = &priv->tx_stats[p54_queue];

	spin_lock_irqsave(&priv->tx_stats_lock, flags);
	if (unlikely(queue->len >= queue->limit && IS_QOS_QUEUE(p54_queue))) {
		spin_unlock_irqrestore(&priv->tx_stats_lock, flags);
		return -ENOSPC;
	}

	queue->len++;
	queue->count++;

	if (unlikely(queue->len == queue->limit && IS_QOS_QUEUE(p54_queue))) {
		u16 ac_queue = p54_queue - P54_QUEUE_DATA;
		ieee80211_stop_queue(priv->hw, ac_queue);
	}

	spin_unlock_irqrestore(&priv->tx_stats_lock, flags);
	return 0;
}