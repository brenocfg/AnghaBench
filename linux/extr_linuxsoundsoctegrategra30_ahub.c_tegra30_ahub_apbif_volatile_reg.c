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
 int /*<<< orphan*/  CHANNEL_CLEAR ; 
 int /*<<< orphan*/  CHANNEL_RXFIFO ; 
 int /*<<< orphan*/  CHANNEL_STATUS ; 
 int /*<<< orphan*/  CHANNEL_TXFIFO ; 
 int /*<<< orphan*/  DAM_LIVE_STATUS ; 
 scalar_t__ REG_IN_ARRAY (unsigned int,int /*<<< orphan*/ ) ; 
#define  TEGRA30_AHUB_APBDMA_LIVE_STATUS 140 
#define  TEGRA30_AHUB_APBIF_INT_SET 139 
#define  TEGRA30_AHUB_APBIF_INT_STATUS 138 
#define  TEGRA30_AHUB_CONFIG_LINK_CTRL 137 
#define  TEGRA30_AHUB_DAM_INT_SET 136 
#define  TEGRA30_AHUB_DAM_INT_STATUS 135 
#define  TEGRA30_AHUB_I2S_INT_SET 134 
#define  TEGRA30_AHUB_I2S_INT_STATUS 133 
#define  TEGRA30_AHUB_I2S_LIVE_STATUS 132 
#define  TEGRA30_AHUB_MISC_CTRL 131 
#define  TEGRA30_AHUB_SPDIF_INT_SET 130 
#define  TEGRA30_AHUB_SPDIF_INT_STATUS 129 
#define  TEGRA30_AHUB_SPDIF_LIVE_STATUS 128 

__attribute__((used)) static bool tegra30_ahub_apbif_volatile_reg(struct device *dev,
					    unsigned int reg)
{
	switch (reg) {
	case TEGRA30_AHUB_CONFIG_LINK_CTRL:
	case TEGRA30_AHUB_MISC_CTRL:
	case TEGRA30_AHUB_APBDMA_LIVE_STATUS:
	case TEGRA30_AHUB_I2S_LIVE_STATUS:
	case TEGRA30_AHUB_SPDIF_LIVE_STATUS:
	case TEGRA30_AHUB_I2S_INT_STATUS:
	case TEGRA30_AHUB_DAM_INT_STATUS:
	case TEGRA30_AHUB_SPDIF_INT_STATUS:
	case TEGRA30_AHUB_APBIF_INT_STATUS:
	case TEGRA30_AHUB_I2S_INT_SET:
	case TEGRA30_AHUB_DAM_INT_SET:
	case TEGRA30_AHUB_SPDIF_INT_SET:
	case TEGRA30_AHUB_APBIF_INT_SET:
		return true;
	default:
		break;
	}

	if (REG_IN_ARRAY(reg, CHANNEL_CLEAR) ||
	    REG_IN_ARRAY(reg, CHANNEL_STATUS) ||
	    REG_IN_ARRAY(reg, CHANNEL_TXFIFO) ||
	    REG_IN_ARRAY(reg, CHANNEL_RXFIFO) ||
	    REG_IN_ARRAY(reg, DAM_LIVE_STATUS))
		return true;

	return false;
}