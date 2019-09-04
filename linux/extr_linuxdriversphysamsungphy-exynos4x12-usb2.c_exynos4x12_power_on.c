#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct samsung_usb2_phy_instance {TYPE_2__* cfg; int /*<<< orphan*/  ext_cnt; struct samsung_usb2_phy_driver* drv; } ;
struct samsung_usb2_phy_driver {struct samsung_usb2_phy_instance* instances; int /*<<< orphan*/  reg_sys; TYPE_1__* cfg; } ;
struct TYPE_4__ {size_t id; } ;
struct TYPE_3__ {scalar_t__ has_mode_switch; } ;

/* Variables and functions */
 size_t EXYNOS4x12_DEVICE ; 
 size_t EXYNOS4x12_HOST ; 
 size_t EXYNOS4x12_HSIC0 ; 
 size_t EXYNOS4x12_HSIC1 ; 
 int /*<<< orphan*/  EXYNOS_4x12_MODE_SWITCH_DEVICE ; 
 int /*<<< orphan*/  EXYNOS_4x12_MODE_SWITCH_HOST ; 
 int /*<<< orphan*/  EXYNOS_4x12_MODE_SWITCH_MASK ; 
 int /*<<< orphan*/  EXYNOS_4x12_MODE_SWITCH_OFFSET ; 
 int /*<<< orphan*/  exynos4x12_power_on_int (struct samsung_usb2_phy_instance*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int exynos4x12_power_on(struct samsung_usb2_phy_instance *inst)
{
	struct samsung_usb2_phy_driver *drv = inst->drv;

	if (inst->ext_cnt++ > 0)
		return 0;

	if (inst->cfg->id == EXYNOS4x12_HOST) {
		regmap_update_bits(drv->reg_sys, EXYNOS_4x12_MODE_SWITCH_OFFSET,
						EXYNOS_4x12_MODE_SWITCH_MASK,
						EXYNOS_4x12_MODE_SWITCH_HOST);
		exynos4x12_power_on_int(&drv->instances[EXYNOS4x12_DEVICE]);
	}

	if (inst->cfg->id == EXYNOS4x12_DEVICE && drv->cfg->has_mode_switch)
		regmap_update_bits(drv->reg_sys, EXYNOS_4x12_MODE_SWITCH_OFFSET,
						EXYNOS_4x12_MODE_SWITCH_MASK,
						EXYNOS_4x12_MODE_SWITCH_DEVICE);

	if (inst->cfg->id == EXYNOS4x12_HSIC0 ||
		inst->cfg->id == EXYNOS4x12_HSIC1) {
		exynos4x12_power_on_int(&drv->instances[EXYNOS4x12_DEVICE]);
		exynos4x12_power_on_int(&drv->instances[EXYNOS4x12_HOST]);
	}

	exynos4x12_power_on_int(inst);

	return 0;
}