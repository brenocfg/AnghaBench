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
struct rtable {TYPE_1__ dst; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct rtable*) ; 
 int /*<<< orphan*/  LINUX_MIB_ARPFILTER ; 
 int /*<<< orphan*/  __NET_INC_STATS (struct net*,int /*<<< orphan*/ ) ; 
 struct net* dev_net (struct net_device*) ; 
 struct rtable* ip_route_output (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_rt_put (struct rtable*) ; 
 int /*<<< orphan*/  l3mdev_master_ifindex_rcu (struct net_device*) ; 

__attribute__((used)) static int arp_filter(__be32 sip, __be32 tip, struct net_device *dev)
{
	struct rtable *rt;
	int flag = 0;
	/*unsigned long now; */
	struct net *net = dev_net(dev);

	rt = ip_route_output(net, sip, tip, 0, l3mdev_master_ifindex_rcu(dev));
	if (IS_ERR(rt))
		return 1;
	if (rt->dst.dev != dev) {
		__NET_INC_STATS(net, LINUX_MIB_ARPFILTER);
		flag = 1;
	}
	ip_rt_put(rt);
	return flag;
}