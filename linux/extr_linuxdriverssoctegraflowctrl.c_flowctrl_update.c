#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (scalar_t__) ; 
 scalar_t__ WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 scalar_t__ tegra_flowctrl_base ; 
 int /*<<< orphan*/  wmb () ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void flowctrl_update(u8 offset, u32 value)
{
	if (WARN_ONCE(IS_ERR_OR_NULL(tegra_flowctrl_base),
		      "Tegra flowctrl not initialised!\n"))
		return;

	writel(value, tegra_flowctrl_base + offset);

	/* ensure the update has reached the flow controller */
	wmb();
	readl_relaxed(tegra_flowctrl_base + offset);
}