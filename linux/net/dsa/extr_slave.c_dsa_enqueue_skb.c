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
struct sk_buff {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_queue_xmit (struct sk_buff*) ; 
 int /*<<< orphan*/  dsa_slave_netpoll_send_skb (struct net_device*,struct sk_buff*) ; 
 int /*<<< orphan*/  dsa_slave_to_master (struct net_device*) ; 
 int /*<<< orphan*/  netpoll_tx_running (struct net_device*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

netdev_tx_t dsa_enqueue_skb(struct sk_buff *skb, struct net_device *dev)
{
	/* SKB for netpoll still need to be mangled with the protocol-specific
	 * tag to be successfully transmitted
	 */
	if (unlikely(netpoll_tx_running(dev)))
		return dsa_slave_netpoll_send_skb(dev, skb);

	/* Queue the SKB for transmission on the parent interface, but
	 * do not modify its EtherType
	 */
	skb->dev = dsa_slave_to_master(dev);
	dev_queue_xmit(skb);

	return NETDEV_TX_OK;
}