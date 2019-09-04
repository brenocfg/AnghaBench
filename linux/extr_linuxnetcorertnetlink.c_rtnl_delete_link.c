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
struct rtnl_link_ops {int /*<<< orphan*/  (* dellink ) (struct net_device*,int /*<<< orphan*/ *) ;} ;
struct net_device {struct rtnl_link_ops* rtnl_link_ops; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_kill ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdevice_many (int /*<<< orphan*/ *) ; 

int rtnl_delete_link(struct net_device *dev)
{
	const struct rtnl_link_ops *ops;
	LIST_HEAD(list_kill);

	ops = dev->rtnl_link_ops;
	if (!ops || !ops->dellink)
		return -EOPNOTSUPP;

	ops->dellink(dev, &list_kill);
	unregister_netdevice_many(&list_kill);

	return 0;
}