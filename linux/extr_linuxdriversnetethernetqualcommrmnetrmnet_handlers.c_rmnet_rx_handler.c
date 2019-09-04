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
struct sk_buff {scalar_t__ pkt_type; struct net_device* dev; } ;
struct rmnet_port {int rmnet_mode; int /*<<< orphan*/  bridge_ep; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  rx_handler_result_t ;

/* Variables and functions */
 scalar_t__ PACKET_LOOPBACK ; 
#define  RMNET_EPMODE_BRIDGE 129 
#define  RMNET_EPMODE_VND 128 
 int /*<<< orphan*/  RX_HANDLER_CONSUMED ; 
 int /*<<< orphan*/  RX_HANDLER_PASS ; 
 int /*<<< orphan*/  rmnet_bridge_handler (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct rmnet_port* rmnet_get_port (struct net_device*) ; 
 int /*<<< orphan*/  rmnet_map_ingress_handler (struct sk_buff*,struct rmnet_port*) ; 

rx_handler_result_t rmnet_rx_handler(struct sk_buff **pskb)
{
	struct sk_buff *skb = *pskb;
	struct rmnet_port *port;
	struct net_device *dev;

	if (!skb)
		goto done;

	if (skb->pkt_type == PACKET_LOOPBACK)
		return RX_HANDLER_PASS;

	dev = skb->dev;
	port = rmnet_get_port(dev);

	switch (port->rmnet_mode) {
	case RMNET_EPMODE_VND:
		rmnet_map_ingress_handler(skb, port);
		break;
	case RMNET_EPMODE_BRIDGE:
		rmnet_bridge_handler(skb, port->bridge_ep);
		break;
	}

done:
	return RX_HANDLER_CONSUMED;
}