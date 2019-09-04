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
 scalar_t__* flowctrl_offset_cpu_csr ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ tegra_flowctrl_base ; 

u32 flowctrl_read_cpu_csr(unsigned int cpuid)
{
	u8 offset = flowctrl_offset_cpu_csr[cpuid];

	if (WARN_ONCE(IS_ERR_OR_NULL(tegra_flowctrl_base),
		      "Tegra flowctrl not initialised!\n"))
		return 0;

	return readl(tegra_flowctrl_base + offset);
}