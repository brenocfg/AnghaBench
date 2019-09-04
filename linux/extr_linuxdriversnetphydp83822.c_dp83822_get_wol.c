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
typedef  int u16 ;
struct phy_device {int dummy; } ;
struct ethtool_wolinfo {int supported; int wolopts; int* sopass; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP83822_DEVADDR ; 
 int DP83822_WOL_EN ; 
 int DP83822_WOL_MAGIC_EN ; 
 int DP83822_WOL_SECURE_ON ; 
 int /*<<< orphan*/  MII_DP83822_RXSOP1 ; 
 int /*<<< orphan*/  MII_DP83822_RXSOP2 ; 
 int /*<<< orphan*/  MII_DP83822_RXSOP3 ; 
 int /*<<< orphan*/  MII_DP83822_WOL_CFG ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dp83822_get_wol(struct phy_device *phydev,
			    struct ethtool_wolinfo *wol)
{
	int value;
	u16 sopass_val;

	wol->supported = (WAKE_MAGIC | WAKE_MAGICSECURE);
	wol->wolopts = 0;

	value = phy_read_mmd(phydev, DP83822_DEVADDR, MII_DP83822_WOL_CFG);

	if (value & DP83822_WOL_MAGIC_EN)
		wol->wolopts |= WAKE_MAGIC;

	if (value & DP83822_WOL_SECURE_ON) {
		sopass_val = phy_read_mmd(phydev, DP83822_DEVADDR,
					  MII_DP83822_RXSOP1);
		wol->sopass[0] = (sopass_val & 0xff);
		wol->sopass[1] = (sopass_val >> 8);

		sopass_val = phy_read_mmd(phydev, DP83822_DEVADDR,
					  MII_DP83822_RXSOP2);
		wol->sopass[2] = (sopass_val & 0xff);
		wol->sopass[3] = (sopass_val >> 8);

		sopass_val = phy_read_mmd(phydev, DP83822_DEVADDR,
					  MII_DP83822_RXSOP3);
		wol->sopass[4] = (sopass_val & 0xff);
		wol->sopass[5] = (sopass_val >> 8);

		wol->wolopts |= WAKE_MAGICSECURE;
	}

	/* WoL is not enabled so set wolopts to 0 */
	if (!(value & DP83822_WOL_EN))
		wol->wolopts = 0;
}