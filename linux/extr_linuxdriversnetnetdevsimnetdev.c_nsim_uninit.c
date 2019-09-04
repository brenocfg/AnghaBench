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
struct netdevsim {TYPE_1__* sdev; int /*<<< orphan*/  ddir; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ddir; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nsim_bpf_uninit (struct netdevsim*) ; 
 int /*<<< orphan*/  nsim_devlink_teardown (struct netdevsim*) ; 
 int /*<<< orphan*/  nsim_ipsec_teardown (struct netdevsim*) ; 

__attribute__((used)) static void nsim_uninit(struct net_device *dev)
{
	struct netdevsim *ns = netdev_priv(dev);

	nsim_ipsec_teardown(ns);
	nsim_devlink_teardown(ns);
	debugfs_remove_recursive(ns->ddir);
	nsim_bpf_uninit(ns);
	if (!--ns->sdev->refcnt) {
		debugfs_remove_recursive(ns->sdev->ddir);
		kfree(ns->sdev);
	}
}