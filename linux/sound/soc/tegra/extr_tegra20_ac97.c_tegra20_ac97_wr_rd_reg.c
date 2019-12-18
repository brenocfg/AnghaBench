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
#define  TEGRA20_AC97_CMD 133 
#define  TEGRA20_AC97_CTRL 132 
#define  TEGRA20_AC97_FIFO1_SCR 131 
#define  TEGRA20_AC97_FIFO_RX1 130 
#define  TEGRA20_AC97_FIFO_TX1 129 
#define  TEGRA20_AC97_STATUS1 128 

__attribute__((used)) static bool tegra20_ac97_wr_rd_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TEGRA20_AC97_CTRL:
	case TEGRA20_AC97_CMD:
	case TEGRA20_AC97_STATUS1:
	case TEGRA20_AC97_FIFO1_SCR:
	case TEGRA20_AC97_FIFO_TX1:
	case TEGRA20_AC97_FIFO_RX1:
		return true;
	default:
		break;
	}

	return false;
}