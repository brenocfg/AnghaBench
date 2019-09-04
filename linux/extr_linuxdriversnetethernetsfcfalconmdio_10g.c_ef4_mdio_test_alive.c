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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  mmds; int /*<<< orphan*/  prtad; } ;
struct ef4_nic {int /*<<< orphan*/  mac_lock; TYPE_1__ mdio; int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_DEVID1 ; 
 int /*<<< orphan*/  MDIO_DEVID2 ; 
 int __ffs (int /*<<< orphan*/ ) ; 
 int ef4_mdio_check_mmds (struct ef4_nic*,int /*<<< orphan*/ ) ; 
 int ef4_mdio_read (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int ef4_mdio_test_alive(struct ef4_nic *efx)
{
	int rc;
	int devad = __ffs(efx->mdio.mmds);
	u16 physid1, physid2;

	mutex_lock(&efx->mac_lock);

	physid1 = ef4_mdio_read(efx, devad, MDIO_DEVID1);
	physid2 = ef4_mdio_read(efx, devad, MDIO_DEVID2);

	if ((physid1 == 0x0000) || (physid1 == 0xffff) ||
	    (physid2 == 0x0000) || (physid2 == 0xffff)) {
		netif_err(efx, hw, efx->net_dev,
			  "no MDIO PHY present with ID %d\n", efx->mdio.prtad);
		rc = -EINVAL;
	} else {
		rc = ef4_mdio_check_mmds(efx, efx->mdio.mmds);
	}

	mutex_unlock(&efx->mac_lock);
	return rc;
}