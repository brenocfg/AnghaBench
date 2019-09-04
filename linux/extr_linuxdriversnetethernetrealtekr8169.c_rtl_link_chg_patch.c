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
struct rtl8169_private {scalar_t__ mac_version; struct net_device* dev; } ;
struct phy_device {scalar_t__ speed; } ;
struct net_device {struct phy_device* phydev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERIAR_EXGMAC ; 
 int /*<<< orphan*/  ERIAR_MASK_0001 ; 
 int /*<<< orphan*/  ERIAR_MASK_0011 ; 
 int /*<<< orphan*/  ERIAR_MASK_1111 ; 
 scalar_t__ RTL_GIGA_MAC_VER_34 ; 
 scalar_t__ RTL_GIGA_MAC_VER_35 ; 
 scalar_t__ RTL_GIGA_MAC_VER_36 ; 
 scalar_t__ RTL_GIGA_MAC_VER_37 ; 
 scalar_t__ RTL_GIGA_MAC_VER_38 ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  rtl_eri_write (struct rtl8169_private*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_w0w1_eri (struct rtl8169_private*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtl_link_chg_patch(struct rtl8169_private *tp)
{
	struct net_device *dev = tp->dev;
	struct phy_device *phydev = dev->phydev;

	if (!netif_running(dev))
		return;

	if (tp->mac_version == RTL_GIGA_MAC_VER_34 ||
	    tp->mac_version == RTL_GIGA_MAC_VER_38) {
		if (phydev->speed == SPEED_1000) {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x00000011,
				      ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005,
				      ERIAR_EXGMAC);
		} else if (phydev->speed == SPEED_100) {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f,
				      ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005,
				      ERIAR_EXGMAC);
		} else {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f,
				      ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x0000003f,
				      ERIAR_EXGMAC);
		}
		/* Reset packet filter */
		rtl_w0w1_eri(tp, 0xdc, ERIAR_MASK_0001, 0x00, 0x01,
			     ERIAR_EXGMAC);
		rtl_w0w1_eri(tp, 0xdc, ERIAR_MASK_0001, 0x01, 0x00,
			     ERIAR_EXGMAC);
	} else if (tp->mac_version == RTL_GIGA_MAC_VER_35 ||
		   tp->mac_version == RTL_GIGA_MAC_VER_36) {
		if (phydev->speed == SPEED_1000) {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x00000011,
				      ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x00000005,
				      ERIAR_EXGMAC);
		} else {
			rtl_eri_write(tp, 0x1bc, ERIAR_MASK_1111, 0x0000001f,
				      ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_1111, 0x0000003f,
				      ERIAR_EXGMAC);
		}
	} else if (tp->mac_version == RTL_GIGA_MAC_VER_37) {
		if (phydev->speed == SPEED_10) {
			rtl_eri_write(tp, 0x1d0, ERIAR_MASK_0011, 0x4d02,
				      ERIAR_EXGMAC);
			rtl_eri_write(tp, 0x1dc, ERIAR_MASK_0011, 0x0060,
				      ERIAR_EXGMAC);
		} else {
			rtl_eri_write(tp, 0x1d0, ERIAR_MASK_0011, 0x0000,
				      ERIAR_EXGMAC);
		}
	}
}