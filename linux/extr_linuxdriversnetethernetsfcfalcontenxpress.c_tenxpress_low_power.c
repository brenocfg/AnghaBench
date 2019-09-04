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
struct ef4_nic {int phy_mode; } ;

/* Variables and functions */
 int PHY_MODE_LOW_POWER ; 
 int /*<<< orphan*/  TENXPRESS_REQUIRED_DEVS ; 
 int /*<<< orphan*/  ef4_mdio_set_mmds_lpower (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tenxpress_low_power(struct ef4_nic *efx)
{
	ef4_mdio_set_mmds_lpower(
		efx, !!(efx->phy_mode & PHY_MODE_LOW_POWER),
		TENXPRESS_REQUIRED_DEVS);
}