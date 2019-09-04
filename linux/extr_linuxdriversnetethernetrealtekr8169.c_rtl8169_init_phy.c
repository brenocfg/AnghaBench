#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtl8169_private {scalar_t__ mac_version; int /*<<< orphan*/  pci_dev; } ;
struct net_device {TYPE_1__* phydev; } ;
struct TYPE_4__ {scalar_t__ autoneg; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int /*<<< orphan*/  PCI_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  PCI_LATENCY_TIMER ; 
 scalar_t__ RTL_GIGA_MAC_VER_02 ; 
 scalar_t__ RTL_GIGA_MAC_VER_06 ; 
 int /*<<< orphan*/  RTL_W8 (struct rtl8169_private*,int,int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  genphy_soft_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  netif_dbg (struct rtl8169_private*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  pci_write_config_byte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  phy_restart_aneg (TYPE_1__*) ; 
 int /*<<< orphan*/  phy_speed_up (TYPE_1__*) ; 
 int /*<<< orphan*/  rtl_hw_phy_config (struct net_device*) ; 
 int /*<<< orphan*/  rtl_writephy (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static void rtl8169_init_phy(struct net_device *dev, struct rtl8169_private *tp)
{
	rtl_hw_phy_config(dev);

	if (tp->mac_version <= RTL_GIGA_MAC_VER_06) {
		netif_dbg(tp, drv, dev,
			  "Set MAC Reg C+CR Offset 0x82h = 0x01h\n");
		RTL_W8(tp, 0x82, 0x01);
	}

	pci_write_config_byte(tp->pci_dev, PCI_LATENCY_TIMER, 0x40);

	if (tp->mac_version <= RTL_GIGA_MAC_VER_06)
		pci_write_config_byte(tp->pci_dev, PCI_CACHE_LINE_SIZE, 0x08);

	if (tp->mac_version == RTL_GIGA_MAC_VER_02) {
		netif_dbg(tp, drv, dev,
			  "Set MAC Reg C+CR Offset 0x82h = 0x01h\n");
		RTL_W8(tp, 0x82, 0x01);
		netif_dbg(tp, drv, dev,
			  "Set PHY Reg 0x0bh = 0x00h\n");
		rtl_writephy(tp, 0x0b, 0x0000); //w 0x0b 15 0 0
	}

	/* We may have called phy_speed_down before */
	phy_speed_up(dev->phydev);

	genphy_soft_reset(dev->phydev);

	/* It was reported that several chips end up with 10MBit/Half on a
	 * 1GBit link after resuming from S3. For whatever reason the PHY on
	 * these chips doesn't properly start a renegotiation when soft-reset.
	 * Explicitly requesting a renegotiation fixes this.
	 */
	if (dev->phydev->autoneg == AUTONEG_ENABLE)
		phy_restart_aneg(dev->phydev);
}