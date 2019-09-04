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
struct net_device {int flags; } ;
struct kaweth_device {int packet_filter_bitmap; } ;
typedef  int __u16 ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int KAWETH_PACKET_FILTER_ALL_MULTICAST ; 
 int KAWETH_PACKET_FILTER_BROADCAST ; 
 int KAWETH_PACKET_FILTER_DIRECTED ; 
 int KAWETH_PACKET_FILTER_MULTICAST ; 
 int KAWETH_PACKET_FILTER_PROMISCUOUS ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,int) ; 
 int /*<<< orphan*/  netdev_mc_empty (struct net_device*) ; 
 struct kaweth_device* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 

__attribute__((used)) static void kaweth_set_rx_mode(struct net_device *net)
{
	struct kaweth_device *kaweth = netdev_priv(net);

	__u16 packet_filter_bitmap = KAWETH_PACKET_FILTER_DIRECTED |
                                     KAWETH_PACKET_FILTER_BROADCAST |
		                     KAWETH_PACKET_FILTER_MULTICAST;

	netdev_dbg(net, "Setting Rx mode to %d\n", packet_filter_bitmap);

	netif_stop_queue(net);

	if (net->flags & IFF_PROMISC) {
		packet_filter_bitmap |= KAWETH_PACKET_FILTER_PROMISCUOUS;
	}
	else if (!netdev_mc_empty(net) || (net->flags & IFF_ALLMULTI)) {
		packet_filter_bitmap |= KAWETH_PACKET_FILTER_ALL_MULTICAST;
	}

	kaweth->packet_filter_bitmap = packet_filter_bitmap;
	netif_wake_queue(net);
}