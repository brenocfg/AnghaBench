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
#define  TEGRA30_I2S_FLOW_OVER 131 
#define  TEGRA30_I2S_FLOW_STATUS 130 
#define  TEGRA30_I2S_FLOW_TOTAL 129 
#define  TEGRA30_I2S_FLOW_UNDER 128 

__attribute__((used)) static bool tegra30_i2s_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TEGRA30_I2S_FLOW_STATUS:
	case TEGRA30_I2S_FLOW_TOTAL:
	case TEGRA30_I2S_FLOW_OVER:
	case TEGRA30_I2S_FLOW_UNDER:
		return true;
	default:
		return false;
	}
}