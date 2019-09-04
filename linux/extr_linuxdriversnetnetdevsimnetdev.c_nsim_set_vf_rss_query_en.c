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
struct TYPE_2__ {int rss_query_enabled; } ;

/* Variables and functions */
 int EINVAL ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nsim_set_vf_rss_query_en(struct net_device *dev, int vf, bool val)
{
	struct netdevsim *ns = netdev_priv(dev);

	if (vf >= ns->num_vfs)
		return -EINVAL;
	ns->vfconfigs[vf].rss_query_enabled = val;

	return 0;
}