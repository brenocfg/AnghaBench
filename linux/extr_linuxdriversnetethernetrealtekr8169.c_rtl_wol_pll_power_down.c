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
struct rtl8169_private {int /*<<< orphan*/  mii_bus; } ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rtl8169_get_wol (struct rtl8169_private*) ; 
 struct phy_device* mdiobus_get_phy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_speed_down (struct phy_device*,int) ; 
 int /*<<< orphan*/  rtl_wol_suspend_quirk (struct rtl8169_private*) ; 

__attribute__((used)) static bool rtl_wol_pll_power_down(struct rtl8169_private *tp)
{
	struct phy_device *phydev;

	if (!__rtl8169_get_wol(tp))
		return false;

	/* phydev may not be attached to netdevice */
	phydev = mdiobus_get_phy(tp->mii_bus, 0);

	phy_speed_down(phydev, false);
	rtl_wol_suspend_quirk(tp);

	return true;
}