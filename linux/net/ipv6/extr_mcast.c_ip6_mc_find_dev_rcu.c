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
struct TYPE_2__ {struct net_device* dev; } ;
struct rt6_info {TYPE_1__ dst; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct inet6_dev {int /*<<< orphan*/  lock; scalar_t__ dead; } ;
struct in6_addr {int dummy; } ;

/* Variables and functions */
 struct inet6_dev* __in6_dev_get (struct net_device*) ; 
 struct net_device* dev_get_by_index_rcu (struct net*,int) ; 
 int /*<<< orphan*/  ip6_rt_put (struct rt6_info*) ; 
 int /*<<< orphan*/  read_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock_bh (int /*<<< orphan*/ *) ; 
 struct rt6_info* rt6_lookup (struct net*,struct in6_addr const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inet6_dev *ip6_mc_find_dev_rcu(struct net *net,
					     const struct in6_addr *group,
					     int ifindex)
{
	struct net_device *dev = NULL;
	struct inet6_dev *idev = NULL;

	if (ifindex == 0) {
		struct rt6_info *rt = rt6_lookup(net, group, NULL, 0, NULL, 0);

		if (rt) {
			dev = rt->dst.dev;
			ip6_rt_put(rt);
		}
	} else
		dev = dev_get_by_index_rcu(net, ifindex);

	if (!dev)
		return NULL;
	idev = __in6_dev_get(dev);
	if (!idev)
		return NULL;
	read_lock_bh(&idev->lock);
	if (idev->dead) {
		read_unlock_bh(&idev->lock);
		return NULL;
	}
	return idev;
}