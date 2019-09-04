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
struct sun4i_usb_phy_data {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  OTGCTL_ROUTE_MUSB ; 
 scalar_t__ REG_PHY_OTGCTL ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sun4i_usb_phy0_reroute(struct sun4i_usb_phy_data *data, int id_det)
{
	u32 regval;

	regval = readl(data->base + REG_PHY_OTGCTL);
	if (id_det == 0) {
		/* Host mode. Route phy0 to EHCI/OHCI */
		regval &= ~OTGCTL_ROUTE_MUSB;
	} else {
		/* Peripheral mode. Route phy0 to MUSB */
		regval |= OTGCTL_ROUTE_MUSB;
	}
	writel(regval, data->base + REG_PHY_OTGCTL);
}