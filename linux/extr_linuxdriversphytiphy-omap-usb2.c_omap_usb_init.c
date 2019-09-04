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
typedef  int /*<<< orphan*/  u32 ;
struct phy {int dummy; } ;
struct omap_usb {int flags; int /*<<< orphan*/  phy_base; } ;

/* Variables and functions */
 int OMAP_USB2_CALIBRATE_FALSE_DISCONNECT ; 
 int /*<<< orphan*/  USB2PHY_ANA_CONFIG1 ; 
 int /*<<< orphan*/  USB2PHY_DISCON_BYP_LATCH ; 
 int /*<<< orphan*/  omap_usb2_enable_clocks (struct omap_usb*) ; 
 int /*<<< orphan*/  omap_usb_readl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_usb_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_usb* phy_get_drvdata (struct phy*) ; 

__attribute__((used)) static int omap_usb_init(struct phy *x)
{
	struct omap_usb *phy = phy_get_drvdata(x);
	u32 val;

	omap_usb2_enable_clocks(phy);

	if (phy->flags & OMAP_USB2_CALIBRATE_FALSE_DISCONNECT) {
		/*
		 *
		 * Reduce the sensitivity of internal PHY by enabling the
		 * DISCON_BYP_LATCH of the USB2PHY_ANA_CONFIG1 register. This
		 * resolves issues with certain devices which can otherwise
		 * be prone to false disconnects.
		 *
		 */
		val = omap_usb_readl(phy->phy_base, USB2PHY_ANA_CONFIG1);
		val |= USB2PHY_DISCON_BYP_LATCH;
		omap_usb_writel(phy->phy_base, USB2PHY_ANA_CONFIG1, val);
	}

	return 0;
}