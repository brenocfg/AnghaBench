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
struct bcm_ns_usb3 {scalar_t__ dmp; } ;

/* Variables and functions */
 scalar_t__ BCMA_RESET_CTL ; 
 int BCM_NS_USB3_PHY_BASE_ADDR_REG ; 
 int BCM_NS_USB3_PHY_PLL30_BLOCK ; 
 int BCM_NS_USB3_PHY_TX_PMD_BLOCK ; 
 int BCM_NS_USB3_PLLA_CONTROL0 ; 
 int BCM_NS_USB3_TX_PMD_CONTROL1 ; 
 int bcm_ns_usb3_mdio_phy_write (struct bcm_ns_usb3*,int,int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int bcm_ns_usb3_phy_init_ns_ax(struct bcm_ns_usb3 *usb3)
{
	int err;

	/* PLL30 block */
	err = bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
					 BCM_NS_USB3_PHY_PLL30_BLOCK);
	if (err < 0)
		return err;

	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PLLA_CONTROL0, 0x6400);

	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG, 0x80e0);

	bcm_ns_usb3_mdio_phy_write(usb3, 0x02, 0x009c);

	/* Enable SSC */
	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_PHY_BASE_ADDR_REG,
				   BCM_NS_USB3_PHY_TX_PMD_BLOCK);

	bcm_ns_usb3_mdio_phy_write(usb3, 0x02, 0x21d3);

	bcm_ns_usb3_mdio_phy_write(usb3, BCM_NS_USB3_TX_PMD_CONTROL1, 0x1003);

	/* Deasserting USB3 system reset */
	writel(0, usb3->dmp + BCMA_RESET_CTL);

	return 0;
}