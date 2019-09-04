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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_INPUT_DATA_CLK_SEL ; 
 int /*<<< orphan*/  DAP_CTRL_SEL ; 
 unsigned int LAST_REG (int /*<<< orphan*/ ) ; 
 unsigned int TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL ; 
 unsigned int TEGRA20_DAS_DAP_CTRL_SEL ; 

__attribute__((used)) static bool tegra20_das_wr_rd_reg(struct device *dev, unsigned int reg)
{
	if ((reg >= TEGRA20_DAS_DAP_CTRL_SEL) &&
	    (reg <= LAST_REG(DAP_CTRL_SEL)))
		return true;
	if ((reg >= TEGRA20_DAS_DAC_INPUT_DATA_CLK_SEL) &&
	    (reg <= LAST_REG(DAC_INPUT_DATA_CLK_SEL)))
		return true;

	return false;
}