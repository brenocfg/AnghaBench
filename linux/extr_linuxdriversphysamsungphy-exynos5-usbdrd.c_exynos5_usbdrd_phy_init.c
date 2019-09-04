#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct phy_usb_instance {TYPE_1__* phy_cfg; } ;
struct phy {int dummy; } ;
struct exynos5_usbdrd_phy {int /*<<< orphan*/  clk; scalar_t__ reg_phy; } ;
struct TYPE_2__ {int (* set_refclk ) (struct phy_usb_instance*) ;int /*<<< orphan*/  (* phy_init ) (struct exynos5_usbdrd_phy*) ;} ;

/* Variables and functions */
 scalar_t__ EXYNOS5_DRD_LINKSYSTEM ; 
 scalar_t__ EXYNOS5_DRD_PHYCLKRST ; 
 scalar_t__ EXYNOS5_DRD_PHYPARAM0 ; 
 scalar_t__ EXYNOS5_DRD_PHYREG0 ; 
 scalar_t__ EXYNOS5_DRD_PHYRESUME ; 
 scalar_t__ EXYNOS5_DRD_PHYUTMICLKSEL ; 
 int LINKSYSTEM_FLADJ (int) ; 
 int LINKSYSTEM_XHCI_VERSION_CONTROL ; 
 int PHYCLKRST_COMMONONN ; 
 int PHYCLKRST_PORTRESET ; 
 int PHYCLKRST_REF_SSP_EN ; 
 int PHYCLKRST_RETENABLEN ; 
 int PHYCLKRST_SSC_EN ; 
 int PHYPARAM0_REF_USE_PAD ; 
 int PHYUTMICLKSEL_UTMI_CLKSEL ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 struct phy_usb_instance* phy_get_drvdata (struct phy*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (struct exynos5_usbdrd_phy*) ; 
 int stub2 (struct phy_usb_instance*) ; 
 struct exynos5_usbdrd_phy* to_usbdrd_phy (struct phy_usb_instance*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int exynos5_usbdrd_phy_init(struct phy *phy)
{
	int ret;
	u32 reg;
	struct phy_usb_instance *inst = phy_get_drvdata(phy);
	struct exynos5_usbdrd_phy *phy_drd = to_usbdrd_phy(inst);

	ret = clk_prepare_enable(phy_drd->clk);
	if (ret)
		return ret;

	/* Reset USB 3.0 PHY */
	writel(0x0, phy_drd->reg_phy + EXYNOS5_DRD_PHYREG0);
	writel(0x0, phy_drd->reg_phy + EXYNOS5_DRD_PHYRESUME);

	/*
	 * Setting the Frame length Adj value[6:1] to default 0x20
	 * See xHCI 1.0 spec, 5.2.4
	 */
	reg =	LINKSYSTEM_XHCI_VERSION_CONTROL |
		LINKSYSTEM_FLADJ(0x20);
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_LINKSYSTEM);

	reg = readl(phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM0);
	/* Select PHY CLK source */
	reg &= ~PHYPARAM0_REF_USE_PAD;
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYPARAM0);

	/* This bit must be set for both HS and SS operations */
	reg = readl(phy_drd->reg_phy + EXYNOS5_DRD_PHYUTMICLKSEL);
	reg |= PHYUTMICLKSEL_UTMI_CLKSEL;
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYUTMICLKSEL);

	/* UTMI or PIPE3 specific init */
	inst->phy_cfg->phy_init(phy_drd);

	/* reference clock settings */
	reg = inst->phy_cfg->set_refclk(inst);

		/* Digital power supply in normal operating mode */
	reg |=	PHYCLKRST_RETENABLEN |
		/* Enable ref clock for SS function */
		PHYCLKRST_REF_SSP_EN |
		/* Enable spread spectrum */
		PHYCLKRST_SSC_EN |
		/* Power down HS Bias and PLL blocks in suspend mode */
		PHYCLKRST_COMMONONN |
		/* Reset the port */
		PHYCLKRST_PORTRESET;

	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	udelay(10);

	reg &= ~PHYCLKRST_PORTRESET;
	writel(reg, phy_drd->reg_phy + EXYNOS5_DRD_PHYCLKRST);

	clk_disable_unprepare(phy_drd->clk);

	return 0;
}