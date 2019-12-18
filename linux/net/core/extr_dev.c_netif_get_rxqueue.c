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
typedef  int u16 ;
struct sk_buff {struct net_device* dev; } ;
struct netdev_rx_queue {int dummy; } ;
struct net_device {int real_num_rx_queues; int /*<<< orphan*/  name; struct netdev_rx_queue* _rx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ,int,int) ; 
 int skb_get_rx_queue (struct sk_buff*) ; 
 scalar_t__ skb_rx_queue_recorded (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct netdev_rx_queue *netif_get_rxqueue(struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	struct netdev_rx_queue *rxqueue;

	rxqueue = dev->_rx;

	if (skb_rx_queue_recorded(skb)) {
		u16 index = skb_get_rx_queue(skb);

		if (unlikely(index >= dev->real_num_rx_queues)) {
			WARN_ONCE(dev->real_num_rx_queues > 1,
				  "%s received packet on queue %u, but number "
				  "of RX queues is %u\n",
				  dev->name, index, dev->real_num_rx_queues);

			return rxqueue; /* Return first rxqueue */
		}
		rxqueue += index;
	}
	return rxqueue;
}