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
struct net_device_context {int /*<<< orphan*/  nvdev; } ;
struct net_device {int /*<<< orphan*/ * netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_ops ; 
 struct net_device* netdev_master_upper_dev_get (struct net_device*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct net_device *get_netvsc_byref(struct net_device *vf_netdev)
{
	struct net_device_context *net_device_ctx;
	struct net_device *dev;

	dev = netdev_master_upper_dev_get(vf_netdev);
	if (!dev || dev->netdev_ops != &device_ops)
		return NULL;	/* not a netvsc device */

	net_device_ctx = netdev_priv(dev);
	if (!rtnl_dereference(net_device_ctx->nvdev))
		return NULL;	/* device is removed */

	return dev;
}