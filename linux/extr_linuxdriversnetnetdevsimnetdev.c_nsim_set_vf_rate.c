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
struct netdevsim {int num_vfs; TYPE_1__* vfconfigs; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int min_tx_rate; int max_tx_rate; } ;

/* Variables and functions */
 int EINVAL ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nsim_set_vf_rate(struct net_device *dev, int vf, int min, int max)
{
	struct netdevsim *ns = netdev_priv(dev);

	if (vf >= ns->num_vfs)
		return -EINVAL;

	ns->vfconfigs[vf].min_tx_rate = min;
	ns->vfconfigs[vf].max_tx_rate = max;

	return 0;
}