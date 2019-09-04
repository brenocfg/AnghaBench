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
typedef  unsigned int u32 ;
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  MDIO_DEVS1 ; 
 int /*<<< orphan*/  MDIO_DEVS2 ; 
 unsigned int MDIO_DEVS_PHYXS ; 
 int MDIO_MMD_PHYXS ; 
 int __ffs (unsigned int) ; 
 scalar_t__ ef4_mdio_check_mmd (struct ef4_nic*,int) ; 
 int ef4_mdio_read (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_vdbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 

int ef4_mdio_check_mmds(struct ef4_nic *efx, unsigned int mmd_mask)
{
	int mmd = 0, probe_mmd, devs1, devs2;
	u32 devices;

	/* Historically we have probed the PHYXS to find out what devices are
	 * present,but that doesn't work so well if the PHYXS isn't expected
	 * to exist, if so just find the first item in the list supplied. */
	probe_mmd = (mmd_mask & MDIO_DEVS_PHYXS) ? MDIO_MMD_PHYXS :
	    __ffs(mmd_mask);

	/* Check all the expected MMDs are present */
	devs1 = ef4_mdio_read(efx, probe_mmd, MDIO_DEVS1);
	devs2 = ef4_mdio_read(efx, probe_mmd, MDIO_DEVS2);
	if (devs1 < 0 || devs2 < 0) {
		netif_err(efx, hw, efx->net_dev,
			  "failed to read devices present\n");
		return -EIO;
	}
	devices = devs1 | (devs2 << 16);
	if ((devices & mmd_mask) != mmd_mask) {
		netif_err(efx, hw, efx->net_dev,
			  "required MMDs not present: got %x, wanted %x\n",
			  devices, mmd_mask);
		return -ENODEV;
	}
	netif_vdbg(efx, hw, efx->net_dev, "Devices present: %x\n", devices);

	/* Check all required MMDs are responding and happy. */
	while (mmd_mask) {
		if ((mmd_mask & 1) && ef4_mdio_check_mmd(efx, mmd))
			return -EIO;
		mmd_mask = mmd_mask >> 1;
		mmd++;
	}

	return 0;
}