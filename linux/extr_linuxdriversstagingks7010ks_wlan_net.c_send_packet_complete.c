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
struct TYPE_2__ {int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_packets; } ;
struct ks_wlan_private {TYPE_1__ nstats; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ netif_queue_stopped (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 

void send_packet_complete(struct ks_wlan_private *priv, struct sk_buff *skb)
{
	priv->nstats.tx_packets++;

	if (netif_queue_stopped(priv->net_dev))
		netif_wake_queue(priv->net_dev);

	if (skb) {
		priv->nstats.tx_bytes += skb->len;
		dev_kfree_skb(skb);
	}
}