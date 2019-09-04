#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int len; int /*<<< orphan*/  queue_mapping; struct net_device* dev; } ;
struct netvsc_vf_pcpu_stats {unsigned int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct net_device_context {TYPE_1__* vf_stats; } ;
struct net_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  slave_dev_queue_mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_dropped; } ;

/* Variables and functions */
 int NET_XMIT_CN ; 
 int NET_XMIT_SUCCESS ; 
 int dev_queue_xmit (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 TYPE_2__* qdisc_skb_cb (struct sk_buff*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct netvsc_vf_pcpu_stats* this_cpu_ptr (TYPE_1__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int netvsc_vf_xmit(struct net_device *net, struct net_device *vf_netdev,
			  struct sk_buff *skb)
{
	struct net_device_context *ndev_ctx = netdev_priv(net);
	unsigned int len = skb->len;
	int rc;

	skb->dev = vf_netdev;
	skb->queue_mapping = qdisc_skb_cb(skb)->slave_dev_queue_mapping;

	rc = dev_queue_xmit(skb);
	if (likely(rc == NET_XMIT_SUCCESS || rc == NET_XMIT_CN)) {
		struct netvsc_vf_pcpu_stats *pcpu_stats
			= this_cpu_ptr(ndev_ctx->vf_stats);

		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->tx_packets++;
		pcpu_stats->tx_bytes += len;
		u64_stats_update_end(&pcpu_stats->syncp);
	} else {
		this_cpu_inc(ndev_ctx->vf_stats->tx_dropped);
	}

	return rc;
}