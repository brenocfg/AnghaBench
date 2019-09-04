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
struct samsung_usb2_phy_instance {TYPE_1__* cfg; struct samsung_usb2_phy_driver* drv; } ;
struct samsung_usb2_phy_driver {int ref_reg_val; scalar_t__ reg_phy; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  EXYNOS4210_DEVICE 131 
#define  EXYNOS4210_HOST 130 
#define  EXYNOS4210_HSIC0 129 
#define  EXYNOS4210_HSIC1 128 
 scalar_t__ EXYNOS_4210_UPHY1CON ; 
 scalar_t__ EXYNOS_4210_UPHYCLK ; 
 int EXYNOS_4210_UPHYCLK_PHYFSEL_MASK ; 
 int EXYNOS_4210_UPHYCLK_PHYFSEL_OFFSET ; 
 scalar_t__ EXYNOS_4210_UPHYPWR ; 
 int EXYNOS_4210_UPHYPWR_HSIC0 ; 
 int EXYNOS_4210_UPHYPWR_HSIC1 ; 
 int EXYNOS_4210_UPHYPWR_PHY0 ; 
 int EXYNOS_4210_UPHYPWR_PHY1 ; 
 scalar_t__ EXYNOS_4210_UPHYRST ; 
 int EXYNOS_4210_URSTCON_HOST_LINK_ALL ; 
 int EXYNOS_4210_URSTCON_HOST_LINK_P0 ; 
 int EXYNOS_4210_URSTCON_HOST_LINK_P1 ; 
 int EXYNOS_4210_URSTCON_HOST_LINK_P2 ; 
 int EXYNOS_4210_URSTCON_PHY0 ; 
 int EXYNOS_4210_URSTCON_PHY1_ALL ; 
 int EXYNOS_4210_URSTCON_PHY1_P0 ; 
 int EXYNOS_4210_URSTCON_PHY1_P1P2 ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void exynos4210_phy_pwr(struct samsung_usb2_phy_instance *inst, bool on)
{
	struct samsung_usb2_phy_driver *drv = inst->drv;
	u32 rstbits = 0;
	u32 phypwr = 0;
	u32 rst;
	u32 pwr;
	u32 clk;

	switch (inst->cfg->id) {
	case EXYNOS4210_DEVICE:
		phypwr =	EXYNOS_4210_UPHYPWR_PHY0;
		rstbits =	EXYNOS_4210_URSTCON_PHY0;
		break;
	case EXYNOS4210_HOST:
		phypwr =	EXYNOS_4210_UPHYPWR_PHY1;
		rstbits =	EXYNOS_4210_URSTCON_PHY1_ALL |
				EXYNOS_4210_URSTCON_PHY1_P0 |
				EXYNOS_4210_URSTCON_PHY1_P1P2 |
				EXYNOS_4210_URSTCON_HOST_LINK_ALL |
				EXYNOS_4210_URSTCON_HOST_LINK_P0;
		writel(on, drv->reg_phy + EXYNOS_4210_UPHY1CON);
		break;
	case EXYNOS4210_HSIC0:
		phypwr =	EXYNOS_4210_UPHYPWR_HSIC0;
		rstbits =	EXYNOS_4210_URSTCON_PHY1_P1P2 |
				EXYNOS_4210_URSTCON_HOST_LINK_P1;
		break;
	case EXYNOS4210_HSIC1:
		phypwr =	EXYNOS_4210_UPHYPWR_HSIC1;
		rstbits =	EXYNOS_4210_URSTCON_PHY1_P1P2 |
				EXYNOS_4210_URSTCON_HOST_LINK_P2;
		break;
	}

	if (on) {
		clk = readl(drv->reg_phy + EXYNOS_4210_UPHYCLK);
		clk &= ~EXYNOS_4210_UPHYCLK_PHYFSEL_MASK;
		clk |= drv->ref_reg_val << EXYNOS_4210_UPHYCLK_PHYFSEL_OFFSET;
		writel(clk, drv->reg_phy + EXYNOS_4210_UPHYCLK);

		pwr = readl(drv->reg_phy + EXYNOS_4210_UPHYPWR);
		pwr &= ~phypwr;
		writel(pwr, drv->reg_phy + EXYNOS_4210_UPHYPWR);

		rst = readl(drv->reg_phy + EXYNOS_4210_UPHYRST);
		rst |= rstbits;
		writel(rst, drv->reg_phy + EXYNOS_4210_UPHYRST);
		udelay(10);
		rst &= ~rstbits;
		writel(rst, drv->reg_phy + EXYNOS_4210_UPHYRST);
		/* The following delay is necessary for the reset sequence to be
		 * completed */
		udelay(80);
	} else {
		pwr = readl(drv->reg_phy + EXYNOS_4210_UPHYPWR);
		pwr |= phypwr;
		writel(pwr, drv->reg_phy + EXYNOS_4210_UPHYPWR);
	}
}