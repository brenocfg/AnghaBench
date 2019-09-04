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
struct team {int /*<<< orphan*/  lock; } ;
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;
struct net {int dummy; } ;
struct genl_info {int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 size_t TEAM_ATTR_TEAM_IFINDEX ; 
 struct net_device* dev_get_by_index (struct net*,int) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct net* genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 struct team* netdev_priv (struct net_device*) ; 
 int nla_get_u32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  team_netdev_ops ; 

__attribute__((used)) static struct team *team_nl_team_get(struct genl_info *info)
{
	struct net *net = genl_info_net(info);
	int ifindex;
	struct net_device *dev;
	struct team *team;

	if (!info->attrs[TEAM_ATTR_TEAM_IFINDEX])
		return NULL;

	ifindex = nla_get_u32(info->attrs[TEAM_ATTR_TEAM_IFINDEX]);
	dev = dev_get_by_index(net, ifindex);
	if (!dev || dev->netdev_ops != &team_netdev_ops) {
		if (dev)
			dev_put(dev);
		return NULL;
	}

	team = netdev_priv(dev);
	mutex_lock(&team->lock);
	return team;
}