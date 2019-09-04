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
struct ef4_self_tests {int /*<<< orphan*/  phy_ext; } ;
struct ef4_nic {int /*<<< orphan*/  net_dev; int /*<<< orphan*/  mac_lock; TYPE_1__* phy_op; } ;
struct TYPE_2__ {int (* run_tests ) (struct ef4_nic*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_info (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int stub1 (struct ef4_nic*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int ef4_test_phy(struct ef4_nic *efx, struct ef4_self_tests *tests,
			unsigned flags)
{
	int rc;

	if (!efx->phy_op->run_tests)
		return 0;

	mutex_lock(&efx->mac_lock);
	rc = efx->phy_op->run_tests(efx, tests->phy_ext, flags);
	mutex_unlock(&efx->mac_lock);
	if (rc == -EPERM)
		rc = 0;
	else
		netif_info(efx, drv, efx->net_dev,
			   "%s phy selftest\n", rc ? "Failed" : "Passed");

	return rc;
}