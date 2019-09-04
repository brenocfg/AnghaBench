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
struct sk_buff {scalar_t__ len; } ;
struct qtnf_vif {int /*<<< orphan*/  stats64; } ;
struct pcpu_sw_netstats {int /*<<< orphan*/  syncp; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct net_device {TYPE_1__ stats; } ;

/* Variables and functions */
 struct qtnf_vif* qtnf_netdev_get_priv (struct net_device*) ; 
 struct pcpu_sw_netstats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void qtnf_update_tx_stats(struct net_device *ndev, const struct sk_buff *skb)
{
	struct qtnf_vif *vif = qtnf_netdev_get_priv(ndev);
	struct pcpu_sw_netstats *stats64;

	if (unlikely(!vif || !vif->stats64)) {
		ndev->stats.tx_packets++;
		ndev->stats.tx_bytes += skb->len;
		return;
	}

	stats64 = this_cpu_ptr(vif->stats64);

	u64_stats_update_begin(&stats64->syncp);
	stats64->tx_packets++;
	stats64->tx_bytes += skb->len;
	u64_stats_update_end(&stats64->syncp);
}