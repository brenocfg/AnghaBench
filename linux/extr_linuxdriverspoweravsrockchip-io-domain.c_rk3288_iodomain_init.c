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
struct rockchip_iodomain {int /*<<< orphan*/  dev; int /*<<< orphan*/  grf; TYPE_1__* supplies; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RK3288_SOC_CON2 ; 
 int RK3288_SOC_CON2_FLASH0 ; 
 size_t RK3288_SOC_FLASH_SUPPLY_NUM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rk3288_iodomain_init(struct rockchip_iodomain *iod)
{
	int ret;
	u32 val;

	/* if no flash supply we should leave things alone */
	if (!iod->supplies[RK3288_SOC_FLASH_SUPPLY_NUM].reg)
		return;

	/*
	 * set flash0 iodomain to also use this framework
	 * instead of a special gpio.
	 */
	val = RK3288_SOC_CON2_FLASH0 | (RK3288_SOC_CON2_FLASH0 << 16);
	ret = regmap_write(iod->grf, RK3288_SOC_CON2, val);
	if (ret < 0)
		dev_warn(iod->dev, "couldn't update flash0 ctrl\n");
}