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
typedef  int u32 ;
struct xsphy_instance {scalar_t__ port_base; } ;
struct mtk_xsphy {int dummy; } ;
typedef  enum phy_mode { ____Placeholder_phy_mode } phy_mode ;

/* Variables and functions */
 int P2D_FORCE_IDDIG ; 
 int P2D_RG_IDDIG ; 
#define  PHY_MODE_USB_DEVICE 130 
#define  PHY_MODE_USB_HOST 129 
#define  PHY_MODE_USB_OTG 128 
 scalar_t__ XSP_U2PHYDTM1 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void u2_phy_instance_set_mode(struct mtk_xsphy *xsphy,
				     struct xsphy_instance *inst,
				     enum phy_mode mode)
{
	u32 tmp;

	tmp = readl(inst->port_base + XSP_U2PHYDTM1);
	switch (mode) {
	case PHY_MODE_USB_DEVICE:
		tmp |= P2D_FORCE_IDDIG | P2D_RG_IDDIG;
		break;
	case PHY_MODE_USB_HOST:
		tmp |= P2D_FORCE_IDDIG;
		tmp &= ~P2D_RG_IDDIG;
		break;
	case PHY_MODE_USB_OTG:
		tmp &= ~(P2D_FORCE_IDDIG | P2D_RG_IDDIG);
		break;
	default:
		return;
	}
	writel(tmp, inst->port_base + XSP_U2PHYDTM1);
}