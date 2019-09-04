#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int /*<<< orphan*/  lock; } ;
struct sk_buff {int dummy; } ;
struct r8152 {struct sk_buff_head tx_queue; TYPE_1__* netdev; } ;
struct net_device_stats {int /*<<< orphan*/  tx_dropped; } ;
struct TYPE_2__ {struct net_device_stats stats; } ;

/* Variables and functions */
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ skb_queue_empty (struct sk_buff_head*) ; 
 int /*<<< orphan*/  skb_queue_splice_init (struct sk_buff_head*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rtl_drop_queued_tx(struct r8152 *tp)
{
	struct net_device_stats *stats = &tp->netdev->stats;
	struct sk_buff_head skb_head, *tx_queue = &tp->tx_queue;
	struct sk_buff *skb;

	if (skb_queue_empty(tx_queue))
		return;

	__skb_queue_head_init(&skb_head);
	spin_lock_bh(&tx_queue->lock);
	skb_queue_splice_init(tx_queue, &skb_head);
	spin_unlock_bh(&tx_queue->lock);

	while ((skb = __skb_dequeue(&skb_head))) {
		dev_kfree_skb(skb);
		stats->tx_dropped++;
	}
}