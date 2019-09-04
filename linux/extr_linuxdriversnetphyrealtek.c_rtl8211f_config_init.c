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
typedef  int /*<<< orphan*/  u16 ;
struct phy_device {scalar_t__ interface; } ;

/* Variables and functions */
 scalar_t__ PHY_INTERFACE_MODE_RGMII_ID ; 
 scalar_t__ PHY_INTERFACE_MODE_RGMII_TXID ; 
 int /*<<< orphan*/  RTL8211F_TX_DELAY ; 
 int genphy_config_init (struct phy_device*) ; 
 int phy_modify_paged (struct phy_device*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8211f_config_init(struct phy_device *phydev)
{
	int ret;
	u16 val = 0;

	ret = genphy_config_init(phydev);
	if (ret < 0)
		return ret;

	/* enable TX-delay for rgmii-id and rgmii-txid, otherwise disable it */
	if (phydev->interface == PHY_INTERFACE_MODE_RGMII_ID ||
	    phydev->interface == PHY_INTERFACE_MODE_RGMII_TXID)
		val = RTL8211F_TX_DELAY;

	return phy_modify_paged(phydev, 0xd08, 0x11, RTL8211F_TX_DELAY, val);
}