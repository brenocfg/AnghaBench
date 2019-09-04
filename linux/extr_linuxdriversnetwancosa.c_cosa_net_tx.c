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
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct channel_data {struct sk_buff* tx_skb; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  cosa_start_tx (struct channel_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct channel_data* dev_to_chan (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 

__attribute__((used)) static netdev_tx_t cosa_net_tx(struct sk_buff *skb,
				     struct net_device *dev)
{
	struct channel_data *chan = dev_to_chan(dev);

	netif_stop_queue(dev);

	chan->tx_skb = skb;
	cosa_start_tx(chan, skb->data, skb->len);
	return NETDEV_TX_OK;
}