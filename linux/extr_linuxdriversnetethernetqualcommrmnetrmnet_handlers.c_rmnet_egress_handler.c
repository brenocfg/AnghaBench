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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {struct net_device* dev; int /*<<< orphan*/  sk; } ;
struct rmnet_priv {TYPE_2__* pcpu_stats; int /*<<< orphan*/  mux_id; struct net_device* real_dev; } ;
struct rmnet_port {int dummy; } ;
struct net_device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_drops; } ;
struct TYPE_4__ {TYPE_1__ stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct rmnet_priv* netdev_priv (struct net_device*) ; 
 struct rmnet_port* rmnet_get_port (struct net_device*) ; 
 scalar_t__ rmnet_map_egress_handler (struct sk_buff*,struct rmnet_port*,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  rmnet_vnd_tx_fixup (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  sk_pacing_shift_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  this_cpu_inc (int /*<<< orphan*/ ) ; 

void rmnet_egress_handler(struct sk_buff *skb)
{
	struct net_device *orig_dev;
	struct rmnet_port *port;
	struct rmnet_priv *priv;
	u8 mux_id;

	sk_pacing_shift_update(skb->sk, 8);

	orig_dev = skb->dev;
	priv = netdev_priv(orig_dev);
	skb->dev = priv->real_dev;
	mux_id = priv->mux_id;

	port = rmnet_get_port(skb->dev);
	if (!port)
		goto drop;

	if (rmnet_map_egress_handler(skb, port, mux_id, orig_dev))
		goto drop;

	rmnet_vnd_tx_fixup(skb, orig_dev);

	dev_queue_xmit(skb);
	return;

drop:
	this_cpu_inc(priv->pcpu_stats->stats.tx_drops);
	kfree_skb(skb);
}