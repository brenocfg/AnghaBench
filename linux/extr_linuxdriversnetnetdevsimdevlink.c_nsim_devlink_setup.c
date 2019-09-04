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
struct netdevsim {struct devlink* devlink; int /*<<< orphan*/  dev; } ;
struct net {int dummy; } ;
struct devlink {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct devlink* devlink_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devlink_free (struct devlink*) ; 
 int devlink_register (struct devlink*,int /*<<< orphan*/ *) ; 
 int devlink_resources_register (struct devlink*) ; 
 int /*<<< orphan*/  devlink_unregister (struct devlink*) ; 
 int* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_devlink_id ; 
 int /*<<< orphan*/  nsim_devlink_ops ; 
 struct net* nsim_to_net (struct netdevsim*) ; 

int nsim_devlink_setup(struct netdevsim *ns)
{
	struct net *net = nsim_to_net(ns);
	bool *reg_devlink = net_generic(net, nsim_devlink_id);
	struct devlink *devlink;
	int err;

	/* only one device per namespace controls devlink */
	if (!*reg_devlink) {
		ns->devlink = NULL;
		return 0;
	}

	devlink = devlink_alloc(&nsim_devlink_ops, 0);
	if (!devlink)
		return -ENOMEM;

	err = devlink_register(devlink, &ns->dev);
	if (err)
		goto err_devlink_free;

	err = devlink_resources_register(devlink);
	if (err)
		goto err_dl_unregister;

	ns->devlink = devlink;

	*reg_devlink = false;

	return 0;

err_dl_unregister:
	devlink_unregister(devlink);
err_devlink_free:
	devlink_free(devlink);

	return err;
}