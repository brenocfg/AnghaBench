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
typedef  int /*<<< orphan*/  u32 ;
struct samsung_usb2_phy_instance {TYPE_1__* cfg; struct samsung_usb2_phy_driver* drv; } ;
struct samsung_usb2_phy_driver {int /*<<< orphan*/  reg_pmu; } ;
struct TYPE_2__ {int id; } ;

/* Variables and functions */
#define  EXYNOS4x12_DEVICE 131 
#define  EXYNOS4x12_HOST 130 
#define  EXYNOS4x12_HSIC0 129 
#define  EXYNOS4x12_HSIC1 128 
 int /*<<< orphan*/  EXYNOS_4x12_USB_ISOL_HSIC0 ; 
 int /*<<< orphan*/  EXYNOS_4x12_USB_ISOL_HSIC0_OFFSET ; 
 int /*<<< orphan*/  EXYNOS_4x12_USB_ISOL_HSIC1 ; 
 int /*<<< orphan*/  EXYNOS_4x12_USB_ISOL_HSIC1_OFFSET ; 
 int /*<<< orphan*/  EXYNOS_4x12_USB_ISOL_OFFSET ; 
 int /*<<< orphan*/  EXYNOS_4x12_USB_ISOL_OTG ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos4x12_isol(struct samsung_usb2_phy_instance *inst, bool on)
{
	struct samsung_usb2_phy_driver *drv = inst->drv;
	u32 offset;
	u32 mask;

	switch (inst->cfg->id) {
	case EXYNOS4x12_DEVICE:
	case EXYNOS4x12_HOST:
		offset = EXYNOS_4x12_USB_ISOL_OFFSET;
		mask = EXYNOS_4x12_USB_ISOL_OTG;
		break;
	case EXYNOS4x12_HSIC0:
		offset = EXYNOS_4x12_USB_ISOL_HSIC0_OFFSET;
		mask = EXYNOS_4x12_USB_ISOL_HSIC0;
		break;
	case EXYNOS4x12_HSIC1:
		offset = EXYNOS_4x12_USB_ISOL_HSIC1_OFFSET;
		mask = EXYNOS_4x12_USB_ISOL_HSIC1;
		break;
	default:
		return;
	}

	regmap_update_bits(drv->reg_pmu, offset, mask, on ? 0 : mask);
}