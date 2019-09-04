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
struct ef4_nic {scalar_t__ loopback_mode; int /*<<< orphan*/  mdio; int /*<<< orphan*/  phy_mode; } ;

/* Variables and functions */
 int LOOPBACKS_WS ; 
 scalar_t__ LOOPBACK_INTERNAL (struct ef4_nic*) ; 
 int LOOPBACK_MASK (struct ef4_nic*) ; 
 scalar_t__ LOOPBACK_PCS ; 
 scalar_t__ LOOPBACK_PHYXS ; 
 scalar_t__ LOOPBACK_PMAPMD ; 
 unsigned int MDIO_DEVS_AN ; 
 unsigned int MDIO_DEVS_PCS ; 
 unsigned int MDIO_DEVS_PHYXS ; 
 unsigned int MDIO_DEVS_PMAPMD ; 
 scalar_t__ ef4_phy_mode_disabled (int /*<<< orphan*/ ) ; 
 int mdio45_links_ok (int /*<<< orphan*/ *,unsigned int) ; 

bool ef4_mdio_links_ok(struct ef4_nic *efx, unsigned int mmd_mask)
{
	/* If the port is in loopback, then we should only consider a subset
	 * of mmd's */
	if (LOOPBACK_INTERNAL(efx))
		return true;
	else if (LOOPBACK_MASK(efx) & LOOPBACKS_WS)
		return false;
	else if (ef4_phy_mode_disabled(efx->phy_mode))
		return false;
	else if (efx->loopback_mode == LOOPBACK_PHYXS)
		mmd_mask &= ~(MDIO_DEVS_PHYXS |
			      MDIO_DEVS_PCS |
			      MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);
	else if (efx->loopback_mode == LOOPBACK_PCS)
		mmd_mask &= ~(MDIO_DEVS_PCS |
			      MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);
	else if (efx->loopback_mode == LOOPBACK_PMAPMD)
		mmd_mask &= ~(MDIO_DEVS_PMAPMD |
			      MDIO_DEVS_AN);

	return mdio45_links_ok(&efx->mdio, mmd_mask);
}