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
struct rmnet_priv {int /*<<< orphan*/  pcpu_stats; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_pkts; } ;
struct rmnet_pcpu_stats {int /*<<< orphan*/  syncp; TYPE_1__ stats; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct rmnet_priv* netdev_priv (struct net_device*) ; 
 struct rmnet_pcpu_stats* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64_stats_update_begin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_stats_update_end (int /*<<< orphan*/ *) ; 

void rmnet_vnd_rx_fixup(struct sk_buff *skb, struct net_device *dev)
{
	struct rmnet_priv *priv = netdev_priv(dev);
	struct rmnet_pcpu_stats *pcpu_ptr;

	pcpu_ptr = this_cpu_ptr(priv->pcpu_stats);

	u64_stats_update_begin(&pcpu_ptr->syncp);
	pcpu_ptr->stats.rx_pkts++;
	pcpu_ptr->stats.rx_bytes += skb->len;
	u64_stats_update_end(&pcpu_ptr->syncp);
}