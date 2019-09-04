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
#define  EXYNOS4210_DEVICE 129 
#define  EXYNOS4210_HOST 128 
 int /*<<< orphan*/  EXYNOS_4210_USB_ISOL_DEVICE ; 
 int /*<<< orphan*/  EXYNOS_4210_USB_ISOL_DEVICE_OFFSET ; 
 int /*<<< orphan*/  EXYNOS_4210_USB_ISOL_HOST ; 
 int /*<<< orphan*/  EXYNOS_4210_USB_ISOL_HOST_OFFSET ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos4210_isol(struct samsung_usb2_phy_instance *inst, bool on)
{
	struct samsung_usb2_phy_driver *drv = inst->drv;
	u32 offset;
	u32 mask;

	switch (inst->cfg->id) {
	case EXYNOS4210_DEVICE:
		offset = EXYNOS_4210_USB_ISOL_DEVICE_OFFSET;
		mask = EXYNOS_4210_USB_ISOL_DEVICE;
		break;
	case EXYNOS4210_HOST:
		offset = EXYNOS_4210_USB_ISOL_HOST_OFFSET;
		mask = EXYNOS_4210_USB_ISOL_HOST;
		break;
	default:
		return;
	}

	regmap_update_bits(drv->reg_pmu, offset, mask, on ? 0 : mask);
}