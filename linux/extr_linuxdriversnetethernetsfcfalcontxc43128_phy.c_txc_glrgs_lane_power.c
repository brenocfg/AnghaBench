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
 int TXC_GLCMD_L01PD_LBN ; 
 int TXC_GLCMD_L23PD_LBN ; 
 int /*<<< orphan*/  TXC_GLRGS_GLCMD ; 
 int ef4_mdio_read (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_mdio_write (struct ef4_nic*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void txc_glrgs_lane_power(struct ef4_nic *efx, int mmd)
{
	int pd = (1 << TXC_GLCMD_L01PD_LBN) | (1 << TXC_GLCMD_L23PD_LBN);
	int ctl = ef4_mdio_read(efx, mmd, TXC_GLRGS_GLCMD);

	if (!(efx->phy_mode & PHY_MODE_LOW_POWER))
		ctl &= ~pd;
	else
		ctl |= pd;

	ef4_mdio_write(efx, mmd, TXC_GLRGS_GLCMD, ctl);
}