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
struct samsung_usb2_phy_driver {scalar_t__ reg_phy; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  EXYNOS5250_DEVICE 131 
#define  EXYNOS5250_HOST 130 
#define  EXYNOS5250_HSIC0 129 
#define  EXYNOS5250_HSIC1 128 
 scalar_t__ EXYNOS_5250_HOSTPHYCTRL0 ; 
 int EXYNOS_5250_HOSTPHYCTRL0_FORCESLEEP ; 
 int EXYNOS_5250_HOSTPHYCTRL0_FORCESUSPEND ; 
 int EXYNOS_5250_HOSTPHYCTRL0_PHYSWRST ; 
 int EXYNOS_5250_HOSTPHYCTRL0_PHYSWRSTALL ; 
 int EXYNOS_5250_HOSTPHYCTRL0_SIDDQ ; 
 scalar_t__ EXYNOS_5250_HSICPHYCTRL1 ; 
 scalar_t__ EXYNOS_5250_HSICPHYCTRL2 ; 
 int EXYNOS_5250_HSICPHYCTRLX_FORCESLEEP ; 
 int EXYNOS_5250_HSICPHYCTRLX_FORCESUSPEND ; 
 int EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_12 ; 
 int EXYNOS_5250_HSICPHYCTRLX_REFCLKSEL_DEFAULT ; 
 int EXYNOS_5250_HSICPHYCTRLX_SIDDQ ; 
 scalar_t__ EXYNOS_5250_USBOTGSYS ; 
 int EXYNOS_5250_USBOTGSYS_FORCE_SLEEP ; 
 int EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND ; 
 int EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG ; 
 int /*<<< orphan*/  exynos5250_isol (struct samsung_usb2_phy_instance*,int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int exynos5250_power_off(struct samsung_usb2_phy_instance *inst)
{
	struct samsung_usb2_phy_driver *drv = inst->drv;
	u32 ctrl0;
	u32 otg;
	u32 hsic;

	exynos5250_isol(inst, 1);

	switch (inst->cfg->id) {
	case EXYNOS5250_DEVICE:
		otg = readl(drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		otg |= (EXYNOS_5250_USBOTGSYS_FORCE_SUSPEND |
			EXYNOS_5250_USBOTGSYS_SIDDQ_UOTG |
			EXYNOS_5250_USBOTGSYS_FORCE_SLEEP);
		writel(otg, drv->reg_phy + EXYNOS_5250_USBOTGSYS);
		break;
	case EXYNOS5250_HOST:
		ctrl0 = readl(drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);
		ctrl0 |= (EXYNOS_5250_HOSTPHYCTRL0_SIDDQ |
				EXYNOS_5250_HOSTPHYCTRL0_FORCESUSPEND |
				EXYNOS_5250_HOSTPHYCTRL0_FORCESLEEP |
				EXYNOS_5250_HOSTPHYCTRL0_PHYSWRST |
				EXYNOS_5250_HOSTPHYCTRL0_PHYSWRSTALL);
		writel(ctrl0, drv->reg_phy + EXYNOS_5250_HOSTPHYCTRL0);
		break;
	case EXYNOS5250_HSIC0:
	case EXYNOS5250_HSIC1:
		hsic = (EXYNOS_5250_HSICPHYCTRLX_REFCLKDIV_12 |
				EXYNOS_5250_HSICPHYCTRLX_REFCLKSEL_DEFAULT |
				EXYNOS_5250_HSICPHYCTRLX_SIDDQ |
				EXYNOS_5250_HSICPHYCTRLX_FORCESLEEP |
				EXYNOS_5250_HSICPHYCTRLX_FORCESUSPEND
				);
		writel(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL1);
		writel(hsic, drv->reg_phy + EXYNOS_5250_HSICPHYCTRL2);
		break;
	}

	return 0;
}