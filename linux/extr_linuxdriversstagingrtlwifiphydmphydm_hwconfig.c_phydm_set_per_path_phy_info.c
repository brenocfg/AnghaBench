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
typedef  int u8 ;
struct dm_phy_status_info {int* rx_mimo_evm_dbm; int* cfo_tail; int* rx_mimo_signal_quality; scalar_t__* rx_snr; int /*<<< orphan*/ * rx_mimo_signal_strength; scalar_t__* rx_pwr; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  odm_query_rx_pwr_percentage (scalar_t__) ; 

__attribute__((used)) static void phydm_set_per_path_phy_info(u8 rx_path, s8 rx_pwr, s8 rx_evm,
					s8 cfo_tail, s8 rx_snr,
					struct dm_phy_status_info *phy_info)
{
	u8 evm_dbm = 0;
	u8 evm_percentage = 0;

	/* SNR is S(8,1), EVM is S(8,1), CFO is S(8,7) */

	if (rx_evm < 0) {
		/* Calculate EVM in dBm */
		evm_dbm = ((u8)(0 - rx_evm) >> 1);

		/* Calculate EVM in percentage */
		if (evm_dbm >= 33)
			evm_percentage = 100;
		else
			evm_percentage = (evm_dbm << 1) + (evm_dbm);
	}

	phy_info->rx_pwr[rx_path] = rx_pwr;
	phy_info->rx_mimo_evm_dbm[rx_path] = evm_dbm;

	/* CFO = CFO_tail * 312.5 / 2^7 ~= CFO tail * 39/512 (kHz)*/
	phy_info->cfo_tail[rx_path] = cfo_tail;
	phy_info->cfo_tail[rx_path] = ((phy_info->cfo_tail[rx_path] << 5) +
				       (phy_info->cfo_tail[rx_path] << 2) +
				       (phy_info->cfo_tail[rx_path] << 1) +
				       (phy_info->cfo_tail[rx_path])) >>
				      9;

	phy_info->rx_mimo_signal_strength[rx_path] =
		odm_query_rx_pwr_percentage(rx_pwr);
	phy_info->rx_mimo_signal_quality[rx_path] = evm_percentage;
	phy_info->rx_snr[rx_path] = rx_snr >> 1;
}