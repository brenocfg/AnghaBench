#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct yam_port {int /*<<< orphan*/  send_queue; } ;
struct sk_buff {scalar_t__ protocol; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_IP ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  ax25_ip_xmit (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 struct yam_port* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_trans_update (struct net_device*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t yam_send_packet(struct sk_buff *skb,
					 struct net_device *dev)
{
	struct yam_port *yp = netdev_priv(dev);

	if (skb->protocol == htons(ETH_P_IP))
		return ax25_ip_xmit(skb);

	skb_queue_tail(&yp->send_queue, skb);
	netif_trans_update(dev);
	return NETDEV_TX_OK;
}