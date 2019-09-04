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
struct net_device {int dummy; } ;
struct local_info {scalar_t__ iw_mode; int /*<<< orphan*/  proc; scalar_t__ ddev; scalar_t__ dev; } ;
struct hostap_interface {struct local_info* local; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOSTAP_INTERFACE_MAIN ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ IW_MODE_INFRA ; 
 int /*<<< orphan*/  dev_template ; 
 scalar_t__ hostap_add_interface (struct local_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hostap_init_ap_proc (struct local_info*) ; 
 int /*<<< orphan*/  hostap_init_proc (struct local_info*) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_carrier_off (scalar_t__) ; 
 int /*<<< orphan*/  prism2_registers_proc_show ; 
 int /*<<< orphan*/  proc_create_single_data (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct local_info*) ; 

__attribute__((used)) static int hostap_hw_ready(struct net_device *dev)
{
	struct hostap_interface *iface;
	struct local_info *local;

	iface = netdev_priv(dev);
	local = iface->local;
	local->ddev = hostap_add_interface(local, HOSTAP_INTERFACE_MAIN, 0,
					   "", dev_template);

	if (local->ddev) {
		if (local->iw_mode == IW_MODE_INFRA ||
		    local->iw_mode == IW_MODE_ADHOC) {
			netif_carrier_off(local->dev);
			netif_carrier_off(local->ddev);
		}
		hostap_init_proc(local);
#ifndef PRISM2_NO_PROCFS_DEBUG
		proc_create_single_data("registers", 0, local->proc,
				 prism2_registers_proc_show, local);
#endif /* PRISM2_NO_PROCFS_DEBUG */
		hostap_init_ap_proc(local);
		return 0;
	}

	return -1;
}