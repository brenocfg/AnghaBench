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
struct exynos5_usbdrd_phy {scalar_t__ reg_phy; } ;

/* Variables and functions */
 scalar_t__ EXYNOS5_DRD_PHYPARAM0 ; 
 scalar_t__ EXYNOS5_DRD_PHYPARAM1 ; 
 scalar_t__ EXYNOS5_DRD_PHYTEST ; 
 scalar_t__ EXYNOS5_DRD_PHYUTMI ; 
 int /*<<< orphan*/  PHYPARAM0_REF_LOSLEVEL ; 
 int /*<<< orphan*/  PHYPARAM0_REF_LOSLEVEL_MASK ; 
 int /*<<< orphan*/  PHYPARAM1_PCS_TXDEEMPH ; 
 int /*<<< orphan*/  PHYPARAM1_PCS_TXDEEMPH_MASK ; 
 int /*<<< orphan*/  PHYTEST_POWERDOWN_HSP ; 
 int /*<<< orphan*/  PHYUTMI_OTGDISABLE ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void exynos5_usbdrd_utmi_init(struct exynos5_usbdrd_phy *phy_drd)
{
	u32 reg;

	reg = readl(phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM0);
	/* Set Loss-of-Signal Detector sensitivity */
	reg &= ~PHYPARAM0_REF_LOSLEVEL_MASK;
	reg |=	PHYPARAM0_REF_LOSLEVEL;
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM0);

	reg = readl(phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM1);
	/* Set Tx De-Emphasis level */
	reg &= ~PHYPARAM1_PCS_TXDEEMPH_MASK;
	reg |=	PHYPARAM1_PCS_TXDEEMPH;
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM1);

	/* UTMI Power Control */
	writel(PHYUTMI_OTGDISABLE, phy_drd->reg_phy + EXYNOS5_DRD_PHYUTMI);

	reg = readl(phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);
	reg &= ~PHYTEST_POWERDOWN_HSP;
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYTEST);
}