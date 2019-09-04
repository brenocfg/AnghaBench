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
#define  TEGRA20_SPDIF_CH_STA_RX_A 139 
#define  TEGRA20_SPDIF_CH_STA_RX_B 138 
#define  TEGRA20_SPDIF_CH_STA_RX_C 137 
#define  TEGRA20_SPDIF_CH_STA_RX_D 136 
#define  TEGRA20_SPDIF_CH_STA_RX_E 135 
#define  TEGRA20_SPDIF_CH_STA_RX_F 134 
#define  TEGRA20_SPDIF_DATA_FIFO_CSR 133 
#define  TEGRA20_SPDIF_DATA_IN 132 
#define  TEGRA20_SPDIF_DATA_OUT 131 
#define  TEGRA20_SPDIF_STATUS 130 
#define  TEGRA20_SPDIF_USR_DAT_TX_A 129 
#define  TEGRA20_SPDIF_USR_STA_RX_A 128 

__attribute__((used)) static bool tegra20_spdif_volatile_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TEGRA20_SPDIF_STATUS:
	case TEGRA20_SPDIF_DATA_FIFO_CSR:
	case TEGRA20_SPDIF_DATA_OUT:
	case TEGRA20_SPDIF_DATA_IN:
	case TEGRA20_SPDIF_CH_STA_RX_A:
	case TEGRA20_SPDIF_CH_STA_RX_B:
	case TEGRA20_SPDIF_CH_STA_RX_C:
	case TEGRA20_SPDIF_CH_STA_RX_D:
	case TEGRA20_SPDIF_CH_STA_RX_E:
	case TEGRA20_SPDIF_CH_STA_RX_F:
	case TEGRA20_SPDIF_USR_STA_RX_A:
	case TEGRA20_SPDIF_USR_DAT_TX_A:
		return true;
	default:
		return false;
	}
}