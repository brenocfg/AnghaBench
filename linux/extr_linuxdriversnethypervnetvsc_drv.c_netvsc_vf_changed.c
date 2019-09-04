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
struct net_device_context {int /*<<< orphan*/  nvdev; } ;
struct net_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int NOTIFY_DONE ; 
 int NOTIFY_OK ; 
 struct net_device* get_netvsc_byref (struct net_device*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,char*,int /*<<< orphan*/ ) ; 
 struct net_device_context* netdev_priv (struct net_device*) ; 
 int netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netvsc_switch_datapath (struct net_device*,int) ; 
 struct netvsc_device* rtnl_dereference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int netvsc_vf_changed(struct net_device *vf_netdev)
{
	struct net_device_context *net_device_ctx;
	struct netvsc_device *netvsc_dev;
	struct net_device *ndev;
	bool vf_is_up = netif_running(vf_netdev);

	ndev = get_netvsc_byref(vf_netdev);
	if (!ndev)
		return NOTIFY_DONE;

	net_device_ctx = netdev_priv(ndev);
	netvsc_dev = rtnl_dereference(net_device_ctx->nvdev);
	if (!netvsc_dev)
		return NOTIFY_DONE;

	netvsc_switch_datapath(ndev, vf_is_up);
	netdev_info(ndev, "Data path switched %s VF: %s\n",
		    vf_is_up ? "to" : "from", vf_netdev->name);

	return NOTIFY_OK;
}