#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct rockchip_typec_phy {scalar_t__ base; } ;
struct TYPE_3__ {scalar_t__ addr; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* usb3_pll_cfg ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void tcphy_cfg_usb3_pll(struct rockchip_typec_phy *tcphy)
{
	u32 i;

	/* load the configuration of PLL0 */
	for (i = 0; i < ARRAY_SIZE(usb3_pll_cfg); i++)
		writel(usb3_pll_cfg[i].value,
		       tcphy->base + usb3_pll_cfg[i].addr);
}