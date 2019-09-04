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
struct st_wdog {TYPE_1__* syscfg; int /*<<< orphan*/  regmap; int /*<<< orphan*/  warm_reset; } ;
struct TYPE_2__ {int /*<<< orphan*/  enable_mask; scalar_t__ enable_reg; int /*<<< orphan*/  reset_type_mask; scalar_t__ reset_type_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void st_wdog_setup(struct st_wdog *st_wdog, bool enable)
{
	/* Type of watchdog reset - 0: Cold 1: Warm */
	if (st_wdog->syscfg->reset_type_reg)
		regmap_update_bits(st_wdog->regmap,
				   st_wdog->syscfg->reset_type_reg,
				   st_wdog->syscfg->reset_type_mask,
				   st_wdog->warm_reset);

	/* Mask/unmask watchdog reset */
	regmap_update_bits(st_wdog->regmap,
			   st_wdog->syscfg->enable_reg,
			   st_wdog->syscfg->enable_mask,
			   enable ? 0 : st_wdog->syscfg->enable_mask);
}