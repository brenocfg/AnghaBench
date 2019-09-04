#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  protocol; } ;
struct netfront_stats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;
struct netfront_queue {int /*<<< orphan*/  napi; TYPE_2__* info; } ;
struct TYPE_9__ {int pull_to; } ;
struct TYPE_6__ {int /*<<< orphan*/  rx_errors; } ;
struct TYPE_8__ {TYPE_1__ stats; } ;
struct TYPE_7__ {TYPE_3__* netdev; int /*<<< orphan*/  rx_stats; } ;

/* Variables and functions */
 TYPE_5__* NETFRONT_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  __pskb_pull_tail (struct sk_buff*,int) ; 
 struct sk_buff* __skb_dequeue (struct sk_buff_head*) ; 
 scalar_t__ checksum_setup (TYPE_3__*,struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,TYPE_3__*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_reset_network_header (struct sk_buff*) ; 
 struct netfront_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_incoming_queue(struct netfront_queue *queue,
				 struct sk_buff_head *rxq)
{
	struct netfront_stats *rx_stats = this_cpu_ptr(queue->info->rx_stats);
	int packets_dropped = 0;
	struct sk_buff *skb;

	while ((skb = __skb_dequeue(rxq)) != NULL) {
		int pull_to = NETFRONT_SKB_CB(skb)->pull_to;

		if (pull_to > skb_headlen(skb))
			__pskb_pull_tail(skb, pull_to - skb_headlen(skb));

		/* Ethernet work: Delayed to here as it peeks the header. */
		skb->protocol = eth_type_trans(skb, queue->info->netdev);
		skb_reset_network_header(skb);

		if (checksum_setup(queue->info->netdev, skb)) {
			kfree_skb(skb);
			packets_dropped++;
			queue->info->netdev->stats.rx_errors++;
			continue;
		}

		u64_stats_update_begin(&rx_stats->syncp);
		rx_stats->packets++;
		rx_stats->bytes += skb->len;
		u64_stats_update_end(&rx_stats->syncp);

		/* Pass it up. */
		napi_gro_receive(&queue->napi, skb);
	}

	return packets_dropped;
}