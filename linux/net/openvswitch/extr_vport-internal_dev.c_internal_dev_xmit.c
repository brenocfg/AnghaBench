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
struct sk_buff {int len; } ;
struct pcpu_sw_netstats {int tx_bytes; int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  tstats; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_4__ {int /*<<< orphan*/  vport; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 TYPE_2__* internal_dev_priv (struct net_device*) ; 
 scalar_t__ likely (int) ; 
 int ovs_vport_receive (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

__attribute__((used)) static netdev_tx_t
internal_dev_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	int len, err;

	len = skb->len;
	rcu_read_lock();
	err = ovs_vport_receive(internal_dev_priv(netdev)->vport, skb, NULL);
	rcu_read_unlock();

	if (likely(!err)) {
		struct pcpu_sw_netstats *tstats = this_cpu_ptr(netdev->tstats);

		u64_stats_update_begin(&tstats->syncp);
		tstats->tx_bytes += len;
		tstats->tx_packets++;
		u64_stats_update_end(&tstats->syncp);
	} else {
		netdev->stats.tx_errors++;
	}
	return NETDEV_TX_OK;
}