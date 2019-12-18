#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int /*<<< orphan*/  tstamp; } ;
struct TYPE_5__ {int /*<<< orphan*/  syncp; int /*<<< orphan*/  dropped; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; } ;
struct per_cpu_dm_data {TYPE_1__ stats; TYPE_2__ drop_queue; int /*<<< orphan*/  dm_alert_work; } ;
struct net_dm_hw_metadata {int dummy; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_7__ {struct net_dm_hw_metadata* hw_metadata; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_4__* NET_DM_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dm_hw_cpu_data ; 
 int /*<<< orphan*/  ktime_get_real () ; 
 struct net_dm_hw_metadata* net_dm_hw_metadata_clone (struct net_dm_hw_metadata const*) ; 
 int /*<<< orphan*/  net_dm_hw_metadata_free (struct net_dm_hw_metadata*) ; 
 scalar_t__ net_dm_queue_len ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_mac_header_was_set (struct sk_buff*) ; 
 scalar_t__ skb_queue_len (TYPE_2__*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct per_cpu_dm_data* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
net_dm_hw_packet_probe(struct sk_buff *skb,
		       const struct net_dm_hw_metadata *hw_metadata)
{
	struct net_dm_hw_metadata *n_hw_metadata;
	ktime_t tstamp = ktime_get_real();
	struct per_cpu_dm_data *hw_data;
	struct sk_buff *nskb;
	unsigned long flags;

	if (!skb_mac_header_was_set(skb))
		return;

	nskb = skb_clone(skb, GFP_ATOMIC);
	if (!nskb)
		return;

	n_hw_metadata = net_dm_hw_metadata_clone(hw_metadata);
	if (!n_hw_metadata)
		goto free;

	NET_DM_SKB_CB(nskb)->hw_metadata = n_hw_metadata;
	nskb->tstamp = tstamp;

	hw_data = this_cpu_ptr(&dm_hw_cpu_data);

	spin_lock_irqsave(&hw_data->drop_queue.lock, flags);
	if (skb_queue_len(&hw_data->drop_queue) < net_dm_queue_len)
		__skb_queue_tail(&hw_data->drop_queue, nskb);
	else
		goto unlock_free;
	spin_unlock_irqrestore(&hw_data->drop_queue.lock, flags);

	schedule_work(&hw_data->dm_alert_work);

	return;

unlock_free:
	spin_unlock_irqrestore(&hw_data->drop_queue.lock, flags);
	u64_stats_update_begin(&hw_data->stats.syncp);
	hw_data->stats.dropped++;
	u64_stats_update_end(&hw_data->stats.syncp);
	net_dm_hw_metadata_free(n_hw_metadata);
free:
	consume_skb(nskb);
}