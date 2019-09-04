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
struct team_pcpu_stats {unsigned int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_3__ {int (* transmit ) (struct team*,struct sk_buff*) ;} ;
struct team {TYPE_2__* pcpu_stats; TYPE_1__ ops; } ;
struct sk_buff {unsigned int len; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  tx_dropped; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 struct team* netdev_priv (struct net_device*) ; 
 int stub1 (struct team*,struct sk_buff*) ; 
 int team_queue_override_transmit (struct team*,struct sk_buff*) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 
 struct team_pcpu_stats* this_cpu_ptr (TYPE_2__*) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t team_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct team *team = netdev_priv(dev);
	bool tx_success;
	unsigned int len = skb->len;

	tx_success = team_queue_override_transmit(team, skb);
	if (!tx_success)
		tx_success = team->ops.transmit(team, skb);
	if (tx_success) {
		struct team_pcpu_stats *pcpu_stats;

		pcpu_stats = this_cpu_ptr(team->pcpu_stats);
		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->tx_packets++;
		pcpu_stats->tx_bytes += len;
		u64_stats_update_end(&pcpu_stats->syncp);
	} else {
		this_cpu_inc(team->pcpu_stats->tx_dropped);
	}

	return NETDEV_TX_OK;
}