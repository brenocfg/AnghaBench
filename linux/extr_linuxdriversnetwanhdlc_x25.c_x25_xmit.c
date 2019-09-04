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
struct sk_buff {int* data; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int LAPB_CONNECTED ; 
 int LAPB_NOTCONNECTED ; 
 int LAPB_OK ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
#define  X25_IFACE_CONNECT 130 
#define  X25_IFACE_DATA 129 
#define  X25_IFACE_DISCONNECT 128 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int lapb_connect_request (struct net_device*) ; 
 int lapb_data_request (struct net_device*,struct sk_buff*) ; 
 int lapb_disconnect_request (struct net_device*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  x25_connected (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_disconnected (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static netdev_tx_t x25_xmit(struct sk_buff *skb, struct net_device *dev)
{
	int result;


	/* X.25 to LAPB */
	switch (skb->data[0]) {
	case X25_IFACE_DATA:	/* Data to be transmitted */
		skb_pull(skb, 1);
		if ((result = lapb_data_request(dev, skb)) != LAPB_OK)
			dev_kfree_skb(skb);
		return NETDEV_TX_OK;

	case X25_IFACE_CONNECT:
		if ((result = lapb_connect_request(dev))!= LAPB_OK) {
			if (result == LAPB_CONNECTED)
				/* Send connect confirm. msg to level 3 */
				x25_connected(dev, 0);
			else
				netdev_err(dev, "LAPB connect request failed, error code = %i\n",
					   result);
		}
		break;

	case X25_IFACE_DISCONNECT:
		if ((result = lapb_disconnect_request(dev)) != LAPB_OK) {
			if (result == LAPB_NOTCONNECTED)
				/* Send disconnect confirm. msg to level 3 */
				x25_disconnected(dev, 0);
			else
				netdev_err(dev, "LAPB disconnect request failed, error code = %i\n",
					   result);
		}
		break;

	default:		/* to be defined */
		break;
	}

	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}