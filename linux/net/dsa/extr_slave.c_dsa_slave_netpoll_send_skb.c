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
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct dsa_slave_priv {scalar_t__ netpoll; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 struct dsa_slave_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netpoll_send_skb (scalar_t__,struct sk_buff*) ; 

__attribute__((used)) static inline netdev_tx_t dsa_slave_netpoll_send_skb(struct net_device *dev,
						     struct sk_buff *skb)
{
#ifdef CONFIG_NET_POLL_CONTROLLER
	struct dsa_slave_priv *p = netdev_priv(dev);

	if (p->netpoll)
		netpoll_send_skb(p->netpoll, skb);
#else
	BUG();
#endif
	return NETDEV_TX_OK;
}