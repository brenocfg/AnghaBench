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
struct netlink_tap_net {int /*<<< orphan*/  netlink_tap_lock; int /*<<< orphan*/  netlink_tap_all; } ;
struct netlink_tap {int /*<<< orphan*/  module; int /*<<< orphan*/  list; TYPE_1__* dev; } ;
struct net {int dummy; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_NETLINK ; 
 int EINVAL ; 
 int /*<<< orphan*/  __module_get (int /*<<< orphan*/ ) ; 
 struct net* dev_net (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct netlink_tap_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netlink_tap_net_id ; 
 scalar_t__ unlikely (int) ; 

int netlink_add_tap(struct netlink_tap *nt)
{
	struct net *net = dev_net(nt->dev);
	struct netlink_tap_net *nn = net_generic(net, netlink_tap_net_id);

	if (unlikely(nt->dev->type != ARPHRD_NETLINK))
		return -EINVAL;

	mutex_lock(&nn->netlink_tap_lock);
	list_add_rcu(&nt->list, &nn->netlink_tap_all);
	mutex_unlock(&nn->netlink_tap_lock);

	__module_get(nt->module);

	return 0;
}