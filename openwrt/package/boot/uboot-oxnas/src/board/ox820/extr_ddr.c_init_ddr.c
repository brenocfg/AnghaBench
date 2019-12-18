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

/* Variables and functions */
 int /*<<< orphan*/  SYS_CTRL_CLK_DDR ; 
 int /*<<< orphan*/  SYS_CTRL_CLK_DDRCK ; 
 int /*<<< orphan*/  SYS_CTRL_CLK_DDRPHY ; 
 int /*<<< orphan*/  SYS_CTRL_RST_DDR ; 
 int /*<<< orphan*/  SYS_CTRL_RST_DDR_PHY ; 
 int /*<<< orphan*/  ddr_setup (int) ; 
 int /*<<< orphan*/  enable_clock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void init_ddr(int mhz)
{
	/* start clocks */
	enable_clock(SYS_CTRL_CLK_DDRPHY);
	enable_clock(SYS_CTRL_CLK_DDR);
	enable_clock(SYS_CTRL_CLK_DDRCK);

	/* bring phy and core out of reset */
	reset_block(SYS_CTRL_RST_DDR_PHY, 0);
	reset_block(SYS_CTRL_RST_DDR, 0);

	/* DDR runs at half the speed of the CPU */
	ddr_setup(mhz >> 1);
	return;
}