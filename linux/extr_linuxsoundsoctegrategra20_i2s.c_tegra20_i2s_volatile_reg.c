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
#define  TEGRA20_I2S_FIFO1 131 
#define  TEGRA20_I2S_FIFO2 130 
#define  TEGRA20_I2S_FIFO_SCR 129 
#define  TEGRA20_I2S_STATUS 128 

__attribute__((used)) static bool tegra20_i2s_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TEGRA20_I2S_STATUS:
	case TEGRA20_I2S_FIFO_SCR:
	case TEGRA20_I2S_FIFO1:
	case TEGRA20_I2S_FIFO2:
		return true;
	default:
		return false;
	}
}