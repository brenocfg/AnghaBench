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
struct netdevsim {int /*<<< orphan*/  dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 struct netdevsim* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void nsim_free(struct net_device *dev)
{
	struct netdevsim *ns = netdev_priv(dev);

	device_unregister(&ns->dev);
	/* netdev and vf state will be freed out of device_release() */
}