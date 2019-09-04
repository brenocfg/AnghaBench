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
struct netdevsim {int /*<<< orphan*/  netdev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_netdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsim_vfs_disable (struct netdevsim*) ; 
 struct netdevsim* to_nsim (struct device*) ; 

__attribute__((used)) static void nsim_dev_release(struct device *dev)
{
	struct netdevsim *ns = to_nsim(dev);

	nsim_vfs_disable(ns);
	free_netdev(ns->netdev);
}