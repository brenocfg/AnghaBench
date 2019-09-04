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
struct net_device {int dummy; } ;
struct TYPE_2__ {int link; } ;
struct ip6_tnl {TYPE_1__ parms; } ;

/* Variables and functions */
 struct ip6_tnl* netdev_priv (struct net_device const*) ; 

int ip6_tnl_get_iflink(const struct net_device *dev)
{
	struct ip6_tnl *t = netdev_priv(dev);

	return t->parms.link;
}