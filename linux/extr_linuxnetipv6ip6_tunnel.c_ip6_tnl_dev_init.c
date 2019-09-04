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
struct net_device {int /*<<< orphan*/  features; } ;
struct TYPE_2__ {scalar_t__ collect_md; } ;
struct ip6_tnl {TYPE_1__ parms; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETIF_F_NETNS_LOCAL ; 
 int ip6_tnl_dev_init_gen (struct net_device*) ; 
 int /*<<< orphan*/  ip6_tnl_link_config (struct ip6_tnl*) ; 
 struct ip6_tnl* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_keep_dst (struct net_device*) ; 

__attribute__((used)) static int ip6_tnl_dev_init(struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);
	int err = ip6_tnl_dev_init_gen(dev);

	if (err)
		return err;
	ip6_tnl_link_config(t);
	if (t->parms.collect_md) {
		dev->features |= NETIF_F_NETNS_LOCAL;
		netif_keep_dst(dev);
	}
	return 0;
}