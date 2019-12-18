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
 int ENODEV ; 
 int TEGRA20_DAS_DAP_CTRL_SEL ; 
 int TEGRA20_DAS_DAP_CTRL_SEL_DAP_CTRL_SEL_P ; 
 int TEGRA20_DAS_DAP_CTRL_SEL_STRIDE ; 
 int /*<<< orphan*/  das ; 
 int /*<<< orphan*/  tegra20_das_write (int,int) ; 

int tegra20_das_connect_dap_to_dac(int dap, int dac)
{
	u32 addr;
	u32 reg;

	if (!das)
		return -ENODEV;

	addr = TEGRA20_DAS_DAP_CTRL_SEL +
		(dap * TEGRA20_DAS_DAP_CTRL_SEL_STRIDE);
	reg = dac << TEGRA20_DAS_DAP_CTRL_SEL_DAP_CTRL_SEL_P;

	tegra20_das_write(addr, reg);

	return 0;
}