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
struct nlattr {int dummy; } ;
struct netlink_ext_ack {int dummy; } ;
struct netdevsim {TYPE_1__* sdev; } ;
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;
struct net {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 size_t IFLA_LINK ; 
 struct net_device* __dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nla_get_u32 (struct nlattr*) ; 
 int /*<<< orphan*/  nsim_netdev_ops ; 
 int register_netdevice (struct net_device*) ; 

__attribute__((used)) static int nsim_newlink(struct net *src_net, struct net_device *dev,
			struct nlattr *tb[], struct nlattr *data[],
			struct netlink_ext_ack *extack)
{
	struct netdevsim *ns = netdev_priv(dev);

	if (tb[IFLA_LINK]) {
		struct net_device *joindev;
		struct netdevsim *joinns;

		joindev = __dev_get_by_index(src_net,
					     nla_get_u32(tb[IFLA_LINK]));
		if (!joindev)
			return -ENODEV;
		if (joindev->netdev_ops != &nsim_netdev_ops)
			return -EINVAL;

		joinns = netdev_priv(joindev);
		if (!joinns->sdev || !joinns->sdev->refcnt)
			return -EINVAL;
		ns->sdev = joinns->sdev;
	}

	return register_netdevice(dev);
}