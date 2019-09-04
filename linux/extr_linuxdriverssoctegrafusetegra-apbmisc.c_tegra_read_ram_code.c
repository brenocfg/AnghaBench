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
typedef  int u32 ;

/* Variables and functions */
 int PMC_STRAPPING_OPT_A_RAM_CODE_MASK_LONG ; 
 int PMC_STRAPPING_OPT_A_RAM_CODE_MASK_SHORT ; 
 int PMC_STRAPPING_OPT_A_RAM_CODE_SHIFT ; 
 scalar_t__ long_ram_code ; 
 int tegra_read_straps () ; 

u32 tegra_read_ram_code(void)
{
	u32 straps = tegra_read_straps();

	if (long_ram_code)
		straps &= PMC_STRAPPING_OPT_A_RAM_CODE_MASK_LONG;
	else
		straps &= PMC_STRAPPING_OPT_A_RAM_CODE_MASK_SHORT;

	return straps >> PMC_STRAPPING_OPT_A_RAM_CODE_SHIFT;
}