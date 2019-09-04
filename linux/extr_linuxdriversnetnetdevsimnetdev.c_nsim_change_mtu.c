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
struct TYPE_2__ {scalar_t__ prog; } ;
struct netdevsim {TYPE_1__ xdp; } ;
struct net_device {int mtu; } ;

/* Variables and functions */
 int EBUSY ; 
 int NSIM_XDP_MAX_MTU ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nsim_change_mtu(struct net_device *dev, int new_mtu)
{
	struct netdevsim *ns = netdev_priv(dev);

	if (ns->xdp.prog && new_mtu > NSIM_XDP_MAX_MTU)
		return -EBUSY;

	dev->mtu = new_mtu;

	return 0;
}