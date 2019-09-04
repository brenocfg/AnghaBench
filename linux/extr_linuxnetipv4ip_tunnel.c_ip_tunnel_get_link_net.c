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
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ip_tunnel {struct net* net; } ;

/* Variables and functions */
 struct ip_tunnel* netdev_priv (struct net_device const*) ; 

struct net *ip_tunnel_get_link_net(const struct net_device *dev)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);

	return tunnel->net;
}