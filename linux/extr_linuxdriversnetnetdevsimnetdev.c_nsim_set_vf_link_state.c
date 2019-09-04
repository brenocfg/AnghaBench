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
struct TYPE_2__ {int link_state; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IFLA_VF_LINK_STATE_AUTO 130 
#define  IFLA_VF_LINK_STATE_DISABLE 129 
#define  IFLA_VF_LINK_STATE_ENABLE 128 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int nsim_set_vf_link_state(struct net_device *dev, int vf, int state)
{
	struct netdevsim *ns = netdev_priv(dev);

	if (vf >= ns->num_vfs)
		return -EINVAL;

	switch (state) {
	case IFLA_VF_LINK_STATE_AUTO:
	case IFLA_VF_LINK_STATE_ENABLE:
	case IFLA_VF_LINK_STATE_DISABLE:
		break;
	default:
		return -EINVAL;
	}

	ns->vfconfigs[vf].link_state = state;

	return 0;
}