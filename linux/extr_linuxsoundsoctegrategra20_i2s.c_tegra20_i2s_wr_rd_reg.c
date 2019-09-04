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
#define  TEGRA20_I2S_CTRL 137 
#define  TEGRA20_I2S_FIFO1 136 
#define  TEGRA20_I2S_FIFO2 135 
#define  TEGRA20_I2S_FIFO_SCR 134 
#define  TEGRA20_I2S_NW_CTRL 133 
#define  TEGRA20_I2S_PCM_CTRL 132 
#define  TEGRA20_I2S_STATUS 131 
#define  TEGRA20_I2S_TDM_CTRL 130 
#define  TEGRA20_I2S_TDM_TX_RX_CTRL 129 
#define  TEGRA20_I2S_TIMING 128 

__attribute__((used)) static bool tegra20_i2s_wr_rd_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TEGRA20_I2S_CTRL:
	case TEGRA20_I2S_STATUS:
	case TEGRA20_I2S_TIMING:
	case TEGRA20_I2S_FIFO_SCR:
	case TEGRA20_I2S_PCM_CTRL:
	case TEGRA20_I2S_NW_CTRL:
	case TEGRA20_I2S_TDM_CTRL:
	case TEGRA20_I2S_TDM_TX_RX_CTRL:
	case TEGRA20_I2S_FIFO1:
	case TEGRA20_I2S_FIFO2:
		return true;
	default:
		return false;
	}
}