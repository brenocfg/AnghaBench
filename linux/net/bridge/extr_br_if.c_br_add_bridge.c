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
struct net_device {int /*<<< orphan*/ * rtnl_link_ops; } ;
struct net_bridge {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NET_NAME_UNKNOWN ; 
 struct net_device* alloc_netdev (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  br_dev_setup ; 
 int /*<<< orphan*/  br_link_ops ; 
 int /*<<< orphan*/  dev_net_set (struct net_device*,struct net*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int register_netdev (struct net_device*) ; 

int br_add_bridge(struct net *net, const char *name)
{
	struct net_device *dev;
	int res;

	dev = alloc_netdev(sizeof(struct net_bridge), name, NET_NAME_UNKNOWN,
			   br_dev_setup);

	if (!dev)
		return -ENOMEM;

	dev_net_set(dev, net);
	dev->rtnl_link_ops = &br_link_ops;

	res = register_netdev(dev);
	if (res)
		free_netdev(dev);
	return res;
}