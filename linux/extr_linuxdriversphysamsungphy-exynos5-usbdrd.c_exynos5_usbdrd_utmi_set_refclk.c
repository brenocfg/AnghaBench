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
typedef  unsigned int u32 ;
struct phy_usb_instance {int dummy; } ;
struct exynos5_usbdrd_phy {int /*<<< orphan*/  extrefclk; scalar_t__ reg_phy; } ;

/* Variables and functions */
 scalar_t__ EXYNOS5_DRD_PHYCLKRST ; 
 unsigned int PHYCLKRST_FSEL (int /*<<< orphan*/ ) ; 
 unsigned int PHYCLKRST_FSEL_UTMI_MASK ; 
 unsigned int PHYCLKRST_MPLL_MULTIPLIER_MASK ; 
 unsigned int PHYCLKRST_REFCLKSEL_EXT_REFCLK ; 
 unsigned int PHYCLKRST_REFCLKSEL_MASK ; 
 unsigned int PHYCLKRST_SSC_REFCLKSEL_MASK ; 
 unsigned int readl (scalar_t__) ; 
 struct exynos5_usbdrd_phy* to_usbdrd_phy (struct phy_usb_instance*) ; 

__attribute__((used)) static unsigned int
exynos5_usbdrd_utmi_set_refclk(struct phy_usb_instance *inst)
{
	u32 reg;
	struct exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	/* restore any previous reference clock settings */
	reg = readl(phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	reg &= ~PHYCLKRST_REFCLKSEL_MASK;
	reg |=	PHYCLKRST_REFCLKSEL_EXT_REFCLK;

	reg &= ~PHYCLKRST_FSEL_UTMI_MASK |
		PHYCLKRST_MPLL_MULTIPLIER_MASK |
		PHYCLKRST_SSC_REFCLKSEL_MASK;
	reg |= PHYCLKRST_FSEL(phy_drd->extrefclk);

	return reg;
}