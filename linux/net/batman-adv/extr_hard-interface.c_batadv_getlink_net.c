#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_1__* rtnl_link_ops; } ;
struct net {int dummy; } ;
struct TYPE_2__ {struct net* (* get_link_net ) (struct net_device const*) ;} ;

/* Variables and functions */
 struct net* stub1 (struct net_device const*) ; 

__attribute__((used)) static struct net *batadv_getlink_net(const struct net_device *netdev,
				      struct net *fallback_net)
{
	if (!netdev->rtnl_link_ops)
		return fallback_net;

	if (!netdev->rtnl_link_ops->get_link_net)
		return fallback_net;

	return netdev->rtnl_link_ops->get_link_net(netdev);
}