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
struct rockchip_usb_phy {int /*<<< orphan*/  reg_offset; TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIWORD_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UOC_CON0_SIDDQ ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rockchip_usb_phy_power(struct rockchip_usb_phy *phy,
					   bool siddq)
{
	u32 val = HIWORD_UPDATE(siddq ? UOC_CON0_SIDDQ : 0, UOC_CON0_SIDDQ);

	return regmap_write(phy->base->reg_base, phy->reg_offset, val);
}