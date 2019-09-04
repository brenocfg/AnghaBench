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
struct netvsc_device {int dummy; } ;
struct net_device_context {int /*<<< orphan*/  nvdev; int /*<<< orphan*/  vf_netdev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_mc_sync (struct net_device*,struct net_device*) ; 
 int /*<<< orphan*/  dev_uc_sync (struct net_device*,struct net_device*) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 void* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  rndis_filter_update (struct netvsc_device*) ; 

__attribute__((used)) static void netvsc_set_rx_mode(struct net_device *net)
{
	struct net_device_context *ndev_ctx = netdev_priv(net);
	struct net_device *vf_netdev;
	struct netvsc_device *nvdev;

	rcu_read_lock();
	vf_netdev = rcu_dereference(ndev_ctx->vf_netdev);
	if (vf_netdev) {
		dev_uc_sync(vf_netdev, net);
		dev_mc_sync(vf_netdev, net);
	}

	nvdev = rcu_dereference(ndev_ctx->nvdev);
	if (nvdev)
		rndis_filter_update(nvdev);
	rcu_read_unlock();
}