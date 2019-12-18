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
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_7__ {void* pc; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 TYPE_4__* NET_DM_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __skb_queue_tail (TYPE_2__*,struct sk_buff*) ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dm_cpu_data ; 
 int /*<<< orphan*/  ktime_get_real () ; 
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

__attribute__((used)) static void net_dm_packet_trace_kfree_skb_hit(void *ignore,
					      struct sk_buff *skb,
					      void *location)
{
	ktime_t tstamp = ktime_get_real();
	struct per_cpu_dm_data *data;
	struct sk_buff *nskb;
	unsigned long flags;

	if (!skb_mac_header_was_set(skb))
		return;

	nskb = skb_clone(skb, GFP_ATOMIC);
	if (!nskb)
		return;

	NET_DM_SKB_CB(nskb)->pc = location;
	/* Override the timestamp because we care about the time when the
	 * packet was dropped.
	 */
	nskb->tstamp = tstamp;

	data = this_cpu_ptr(&dm_cpu_data);

	spin_lock_irqsave(&data->drop_queue.lock, flags);
	if (skb_queue_len(&data->drop_queue) < net_dm_queue_len)
		__skb_queue_tail(&data->drop_queue, nskb);
	else
		goto unlock_free;
	spin_unlock_irqrestore(&data->drop_queue.lock, flags);

	schedule_work(&data->dm_alert_work);

	return;

unlock_free:
	spin_unlock_irqrestore(&data->drop_queue.lock, flags);
	u64_stats_update_begin(&data->stats.syncp);
	data->stats.dropped++;
	u64_stats_update_end(&data->stats.syncp);
	consume_skb(nskb);
}