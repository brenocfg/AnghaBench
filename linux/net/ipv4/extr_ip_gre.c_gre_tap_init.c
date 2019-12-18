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
struct net_device {int /*<<< orphan*/  priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_LIVE_ADDR_CHANGE ; 
 int /*<<< orphan*/  __gre_tunnel_init (struct net_device*) ; 
 int ip_tunnel_init (struct net_device*) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static int gre_tap_init(struct net_device *dev)
{
	__gre_tunnel_init(dev);
	dev->priv_flags |= IFF_LIVE_ADDR_CHANGE;
	netif_keep_dst(dev);

	return ip_tunnel_init(dev);
}