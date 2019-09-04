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
struct ef4_nic {int phy_mode; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int PHY_MODE_SPECIAL ; 
 int ef4_check_disabled (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_link_status_changed (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_selftest_async_start (struct ef4_nic*) ; 
 int /*<<< orphan*/  ef4_start_all (struct ef4_nic*) ; 
 int /*<<< orphan*/  ifup ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 

int ef4_net_open(struct net_device *net_dev)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	int rc;

	netif_dbg(efx, ifup, efx->net_dev, "opening device on CPU %d\n",
		  raw_smp_processor_id());

	rc = ef4_check_disabled(efx);
	if (rc)
		return rc;
	if (efx->phy_mode & PHY_MODE_SPECIAL)
		return -EBUSY;

	/* Notify the kernel of the link state polled during driver load,
	 * before the monitor starts running */
	ef4_link_status_changed(efx);

	ef4_start_all(efx);
	ef4_selftest_async_start(efx);
	return 0;
}