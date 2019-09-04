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
#define  TEGRA20_SPDIF_CH_STA_RX_A 147 
#define  TEGRA20_SPDIF_CH_STA_RX_B 146 
#define  TEGRA20_SPDIF_CH_STA_RX_C 145 
#define  TEGRA20_SPDIF_CH_STA_RX_D 144 
#define  TEGRA20_SPDIF_CH_STA_RX_E 143 
#define  TEGRA20_SPDIF_CH_STA_RX_F 142 
#define  TEGRA20_SPDIF_CH_STA_TX_A 141 
#define  TEGRA20_SPDIF_CH_STA_TX_B 140 
#define  TEGRA20_SPDIF_CH_STA_TX_C 139 
#define  TEGRA20_SPDIF_CH_STA_TX_D 138 
#define  TEGRA20_SPDIF_CH_STA_TX_E 137 
#define  TEGRA20_SPDIF_CH_STA_TX_F 136 
#define  TEGRA20_SPDIF_CTRL 135 
#define  TEGRA20_SPDIF_DATA_FIFO_CSR 134 
#define  TEGRA20_SPDIF_DATA_IN 133 
#define  TEGRA20_SPDIF_DATA_OUT 132 
#define  TEGRA20_SPDIF_STATUS 131 
#define  TEGRA20_SPDIF_STROBE_CTRL 130 
#define  TEGRA20_SPDIF_USR_DAT_TX_A 129 
#define  TEGRA20_SPDIF_USR_STA_RX_A 128 

__attribute__((used)) static bool tegra20_spdif_wr_rd_reg(struct device *dev, unsigned int reg)
{
	switch (reg) {
	case TEGRA20_SPDIF_CTRL:
	case TEGRA20_SPDIF_STATUS:
	case TEGRA20_SPDIF_STROBE_CTRL:
	case TEGRA20_SPDIF_DATA_FIFO_CSR:
	case TEGRA20_SPDIF_DATA_OUT:
	case TEGRA20_SPDIF_DATA_IN:
	case TEGRA20_SPDIF_CH_STA_RX_A:
	case TEGRA20_SPDIF_CH_STA_RX_B:
	case TEGRA20_SPDIF_CH_STA_RX_C:
	case TEGRA20_SPDIF_CH_STA_RX_D:
	case TEGRA20_SPDIF_CH_STA_RX_E:
	case TEGRA20_SPDIF_CH_STA_RX_F:
	case TEGRA20_SPDIF_CH_STA_TX_A:
	case TEGRA20_SPDIF_CH_STA_TX_B:
	case TEGRA20_SPDIF_CH_STA_TX_C:
	case TEGRA20_SPDIF_CH_STA_TX_D:
	case TEGRA20_SPDIF_CH_STA_TX_E:
	case TEGRA20_SPDIF_CH_STA_TX_F:
	case TEGRA20_SPDIF_USR_STA_RX_A:
	case TEGRA20_SPDIF_USR_DAT_TX_A:
		return true;
	default:
		return false;
	}
}