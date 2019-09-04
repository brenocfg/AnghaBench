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
struct netdevsim {int /*<<< orphan*/ * devlink; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_resources_unregister (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devlink_unregister (int /*<<< orphan*/ *) ; 
 int* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_devlink_id ; 
 int /*<<< orphan*/  nsim_devlink_net_reset (struct net*) ; 
 struct net* nsim_to_net (struct netdevsim*) ; 

void nsim_devlink_teardown(struct netdevsim *ns)
{
	if (ns->devlink) {
		struct net *net = nsim_to_net(ns);
		bool *reg_devlink = net_generic(net, nsim_devlink_id);

		devlink_resources_unregister(ns->devlink, NULL);
		devlink_unregister(ns->devlink);
		devlink_free(ns->devlink);
		ns->devlink = NULL;

		nsim_devlink_net_reset(net);
		*reg_devlink = true;
	}
}