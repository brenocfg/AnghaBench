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
struct netvsc_device {int /*<<< orphan*/  subchan_work; } ;
struct net_device_context {int /*<<< orphan*/  vf_stats; int /*<<< orphan*/  list; int /*<<< orphan*/  vf_netdev; int /*<<< orphan*/  nvdev; int /*<<< orphan*/  dwork; } ;
struct net_device {int dummy; } ;
struct hv_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_netdev (struct net_device*) ; 
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 struct net_device* hv_get_drvdata (struct hv_device*) ; 
 int /*<<< orphan*/  hv_set_drvdata (struct hv_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netvsc_unregister_vf (struct net_device*) ; 
 int /*<<< orphan*/  rndis_filter_device_remove (struct hv_device*,struct netvsc_device*) ; 
 void* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int /*<<< orphan*/  unregister_netdevice (struct net_device*) ; 

__attribute__((used)) static int netvsc_remove(struct hv_device *dev)
{
	struct net_device_context *ndev_ctx;
	struct net_device *vf_netdev, *net;
	struct netvsc_device *nvdev;

	net = hv_get_drvdata(dev);
	if (net == NULL) {
		dev_err(&dev->device, "No net device to remove\n");
		return 0;
	}

	ndev_ctx = netdev_priv(net);

	cancel_delayed_work_sync(&ndev_ctx->dwork);

	rtnl_lock();
	nvdev = rtnl_dereference(ndev_ctx->nvdev);
	if (nvdev)
		cancel_work_sync(&nvdev->subchan_work);

	/*
	 * Call to the vsc driver to let it know that the device is being
	 * removed. Also blocks mtu and channel changes.
	 */
	vf_netdev = rtnl_dereference(ndev_ctx->vf_netdev);
	if (vf_netdev)
		netvsc_unregister_vf(vf_netdev);

	if (nvdev)
		rndis_filter_device_remove(dev, nvdev);

	unregister_netdevice(net);
	list_del(&ndev_ctx->list);

	rtnl_unlock();

	hv_set_drvdata(dev, NULL);

	free_percpu(ndev_ctx->vf_stats);
	free_netdev(net);
	return 0;
}