#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct phy_status_rpt_8812 {int* cfosho; int* gain_trsw; int* gain_trsw_cd; int* rxsnr; int* csi_current; int* cfotail; int pwdb_all; int /*<<< orphan*/  antidx_antd; int /*<<< orphan*/  antidx_antc; int /*<<< orphan*/  antidx_antb; int /*<<< orphan*/  antidx_anta; int /*<<< orphan*/  hw_antsw_occur; } ;
struct fast_antenna_training {int /*<<< orphan*/  antsel_rx_keep_3; int /*<<< orphan*/  antsel_rx_keep_2; int /*<<< orphan*/  antsel_rx_keep_1; int /*<<< orphan*/  antsel_rx_keep_0; int /*<<< orphan*/  hw_antsw_occur; } ;
struct TYPE_2__ {int* rx_snr_db; int /*<<< orphan*/  num_qry_phy_status_ofdm; int /*<<< orphan*/  num_qry_phy_status_cck; } ;
struct phy_dm_struct {int curr_station_id; int is_cck_high_power; int support_ic_type; int cck_lna_idx; int cck_vga_idx; scalar_t__ support_platform; int patch_id; int rf_path_rx_enable; int rx_pwdb_ave; struct fast_antenna_training dm_fat_table; int /*<<< orphan*/  is_mp_chip; TYPE_1__ phy_dbg_info; } ;
struct dm_phy_status_info {int* rx_mimo_signal_quality; int rx_pwdb_all; int bt_rx_rssi_percentage; int recv_signal_power; int signal_quality; int* rx_mimo_signal_strength; int* rx_pwr; int* rx_snr; int rx_power; int* rx_mimo_evm_dbm; int signal_strength; void** cfo_tail; void** cfo_short; } ;
struct dm_per_pkt_info {scalar_t__ data_rate; int station_id; scalar_t__ is_to_self; } ;
typedef  int s8 ;

/* Variables and functions */
 int BIT (int) ; 
 scalar_t__ ODM_RATE11M ; 
 scalar_t__ ODM_RATEMCS15 ; 
 scalar_t__ ODM_RATEMCS16 ; 
 scalar_t__ ODM_RATEMCS23 ; 
 scalar_t__ ODM_RATEMCS8 ; 
 scalar_t__ ODM_RATEVHTSS2MCS0 ; 
 scalar_t__ ODM_RATEVHTSS2MCS9 ; 
 scalar_t__ ODM_RATEVHTSS3MCS0 ; 
 scalar_t__ ODM_RATEVHTSS3MCS9 ; 
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 
 size_t ODM_RF_PATH_C ; 
 size_t ODM_RF_PATH_D ; 
 int ODM_RF_PATH_MAX_JAGUAR ; 
 int ODM_RTL8812 ; 
 int ODM_RTL8814A ; 
 int ODM_RTL8821 ; 
 int ODM_RTL8822B ; 
 int ODM_RTL8881A ; 
 scalar_t__ ODM_WIN ; 
 int RT_CID_819X_LENOVO ; 
 void* odm_cfo (int) ; 
 int /*<<< orphan*/  odm_parsing_cfo (struct phy_dm_struct*,struct dm_per_pkt_info*,int*,int) ; 
 int odm_query_rx_pwr_percentage (int) ; 
 int /*<<< orphan*/  odm_rx_phy_bw_jaguar_series_parsing (struct dm_phy_status_info*,struct dm_per_pkt_info*,struct phy_status_rpt_8812*) ; 
 scalar_t__ odm_signal_scale_mapping (struct phy_dm_struct*,int) ; 
 int odm_sq_process_patch_rt_cid_819x_lenovo (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int phydm_adjust_pwdb (int,int) ; 
 int phydm_get_evm_dbm (int,int,struct phy_status_rpt_8812*,struct dm_phy_status_info*) ; 
 int phydm_get_odm_evm (int,struct dm_per_pkt_info*,struct phy_status_rpt_8812*) ; 
 int phydm_get_rx_pwr (int,int,int) ; 
 int phydm_get_signal_quality_8812 (struct dm_phy_status_info*,struct phy_dm_struct*,struct phy_status_rpt_8812*) ; 
 int phydm_rate_to_num_ss (struct phy_dm_struct*,scalar_t__) ; 

__attribute__((used)) static void odm_rx_phy_status_jaguar_series_parsing(
	struct phy_dm_struct *dm, struct dm_phy_status_info *phy_info,
	u8 *phy_status, struct dm_per_pkt_info *pktinfo)
{
	u8 i, max_spatial_stream;
	s8 rx_pwr[4], rx_pwr_all = 0;
	u8 EVM = 0, evm_dbm, pwdb_all = 0, pwdb_all_bt;
	u8 RSSI, avg_rssi = 0, best_rssi = 0, second_rssi = 0;
	u8 is_cck_rate = 0;
	u8 rf_rx_num = 0;
	u8 cck_highpwr = 0;
	u8 LNA_idx, VGA_idx;
	struct phy_status_rpt_8812 *phy_sta_rpt =
		(struct phy_status_rpt_8812 *)phy_status;
	struct fast_antenna_training *fat_tab = &dm->dm_fat_table;
	u8 num_ss;

	odm_rx_phy_bw_jaguar_series_parsing(phy_info, pktinfo, phy_sta_rpt);

	if (pktinfo->data_rate <= ODM_RATE11M)
		is_cck_rate = true;
	else
		is_cck_rate = false;

	if (pktinfo->is_to_self)
		dm->curr_station_id = pktinfo->station_id;
	else
		dm->curr_station_id = 0xff;

	phy_info->rx_mimo_signal_quality[ODM_RF_PATH_A] = -1;
	phy_info->rx_mimo_signal_quality[ODM_RF_PATH_B] = -1;
	phy_info->rx_mimo_signal_quality[ODM_RF_PATH_C] = -1;
	phy_info->rx_mimo_signal_quality[ODM_RF_PATH_D] = -1;

	if (is_cck_rate) {
		u8 cck_agc_rpt;

		dm->phy_dbg_info.num_qry_phy_status_cck++;

		/*(1)Hardware does not provide RSSI for CCK*/
		/*(2)PWDB, Average PWDB calculated by hardware (for RA)*/

		cck_highpwr = dm->is_cck_high_power;

		cck_agc_rpt = phy_sta_rpt->cfosho[0];
		LNA_idx = ((cck_agc_rpt & 0xE0) >> 5);
		VGA_idx = (cck_agc_rpt & 0x1F);

		if (dm->support_ic_type == ODM_RTL8812) {
			rx_pwr_all =
				phydm_get_rx_pwr(LNA_idx, VGA_idx, cck_highpwr);
			rx_pwr_all += 6;
			pwdb_all = odm_query_rx_pwr_percentage(rx_pwr_all);
			pwdb_all = phydm_adjust_pwdb(cck_highpwr, pwdb_all);

		} else if (dm->support_ic_type & (ODM_RTL8821 | ODM_RTL8881A)) {
			s8 pout = -6;

			switch (LNA_idx) {
			case 5:
				rx_pwr_all = pout - 32 - (2 * VGA_idx);
				break;
			case 4:
				rx_pwr_all = pout - 24 - (2 * VGA_idx);
				break;
			case 2:
				rx_pwr_all = pout - 11 - (2 * VGA_idx);
				break;
			case 1:
				rx_pwr_all = pout + 5 - (2 * VGA_idx);
				break;
			case 0:
				rx_pwr_all = pout + 21 - (2 * VGA_idx);
				break;
			}
			pwdb_all = odm_query_rx_pwr_percentage(rx_pwr_all);
		} else if (dm->support_ic_type == ODM_RTL8814A ||
			   dm->support_ic_type == ODM_RTL8822B) {
			s8 pout = -6;

			switch (LNA_idx) {
			/*CCK only use LNA: 2, 3, 5, 7*/
			case 7:
				rx_pwr_all = pout - 32 - (2 * VGA_idx);
				break;
			case 5:
				rx_pwr_all = pout - 22 - (2 * VGA_idx);
				break;
			case 3:
				rx_pwr_all = pout - 2 - (2 * VGA_idx);
				break;
			case 2:
				rx_pwr_all = pout + 5 - (2 * VGA_idx);
				break;
			default:
				break;
			}
			pwdb_all = odm_query_rx_pwr_percentage(rx_pwr_all);
		}

		dm->cck_lna_idx = LNA_idx;
		dm->cck_vga_idx = VGA_idx;
		phy_info->rx_pwdb_all = pwdb_all;
		phy_info->bt_rx_rssi_percentage = pwdb_all;
		phy_info->recv_signal_power = rx_pwr_all;
		/*(3) Get Signal Quality (EVM)*/
		{
			u8 sq;

			if ((dm->support_platform == ODM_WIN) &&
			    (dm->patch_id == RT_CID_819X_LENOVO))
				sq = odm_sq_process_patch_rt_cid_819x_lenovo(
					dm, is_cck_rate, pwdb_all, 0, 0);
			else
				sq = phydm_get_signal_quality_8812(phy_info, dm,
								   phy_sta_rpt);

			phy_info->signal_quality = sq;
			phy_info->rx_mimo_signal_quality[ODM_RF_PATH_A] = sq;
		}

		for (i = ODM_RF_PATH_A; i < ODM_RF_PATH_MAX_JAGUAR; i++) {
			if (i == 0)
				phy_info->rx_mimo_signal_strength[0] = pwdb_all;
			else
				phy_info->rx_mimo_signal_strength[i] = 0;
		}
	} else {
		/*is OFDM rate*/
		fat_tab->hw_antsw_occur = phy_sta_rpt->hw_antsw_occur;

		dm->phy_dbg_info.num_qry_phy_status_ofdm++;

		/*(1)Get RSSI for OFDM rate*/

		for (i = ODM_RF_PATH_A; i < ODM_RF_PATH_MAX_JAGUAR; i++) {
			/*2008/01/30 MH we will judge RF RX path now.*/
			if (dm->rf_path_rx_enable & BIT(i))
				rf_rx_num++;
			/*2012.05.25 LukeLee: Testchip AGC report is wrong,
			 *it should be restored back to old formula in MP chip
			 */
			if (i < ODM_RF_PATH_C)
				rx_pwr[i] = (phy_sta_rpt->gain_trsw[i] & 0x7F) -
					    110;
			else
				rx_pwr[i] = (phy_sta_rpt->gain_trsw_cd[i - 2] &
					     0x7F) -
					    110;

			phy_info->rx_pwr[i] = rx_pwr[i];

			/* Translate DBM to percentage. */
			RSSI = odm_query_rx_pwr_percentage(rx_pwr[i]);

			/*total_rssi += RSSI;*/
			/*Get the best two RSSI*/
			if (RSSI > best_rssi && RSSI > second_rssi) {
				second_rssi = best_rssi;
				best_rssi = RSSI;
			} else if (RSSI > second_rssi && RSSI <= best_rssi) {
				second_rssi = RSSI;
			}

			phy_info->rx_mimo_signal_strength[i] = (u8)RSSI;

			/*Get Rx snr value in DB*/
			if (i < ODM_RF_PATH_C)
				phy_info->rx_snr[i] =
					dm->phy_dbg_info.rx_snr_db[i] =
						phy_sta_rpt->rxsnr[i] / 2;
			else if (dm->support_ic_type &
				 (ODM_RTL8814A | ODM_RTL8822B))
				phy_info->rx_snr[i] = dm->phy_dbg_info
							      .rx_snr_db[i] =
					phy_sta_rpt->csi_current[i - 2] / 2;

			/*(2) CFO_short  & CFO_tail*/
			if (i < ODM_RF_PATH_C) {
				phy_info->cfo_short[i] =
					odm_cfo((phy_sta_rpt->cfosho[i]));
				phy_info->cfo_tail[i] =
					odm_cfo((phy_sta_rpt->cfotail[i]));
			}
		}

		/*(3)PWDB, Average PWDB calculated by hardware (for RA)*/

		/*2012.05.25 LukeLee: Testchip AGC report is wrong, it should be
		 *restored back to old formula in MP chip
		 */
		if ((dm->support_ic_type &
		     (ODM_RTL8812 | ODM_RTL8821 | ODM_RTL8881A)) &&
		    (!dm->is_mp_chip))
			rx_pwr_all = (phy_sta_rpt->pwdb_all & 0x7f) - 110;
		else
			rx_pwr_all = (((phy_sta_rpt->pwdb_all) >> 1) & 0x7f) -
				     110; /*OLD FORMULA*/

		pwdb_all = odm_query_rx_pwr_percentage(rx_pwr_all);
		pwdb_all_bt = pwdb_all;

		phy_info->rx_pwdb_all = pwdb_all;
		phy_info->bt_rx_rssi_percentage = pwdb_all_bt;
		phy_info->rx_power = rx_pwr_all;
		phy_info->recv_signal_power = rx_pwr_all;

		if ((dm->support_platform == ODM_WIN) && (dm->patch_id == 19)) {
			/*do nothing*/
		} else {
			/*mgnt_info->customer_id != RT_CID_819X_LENOVO*/

			/*(4)EVM of OFDM rate*/

			if ((pktinfo->data_rate >= ODM_RATEMCS8) &&
			    (pktinfo->data_rate <= ODM_RATEMCS15))
				max_spatial_stream = 2;
			else if ((pktinfo->data_rate >= ODM_RATEVHTSS2MCS0) &&
				 (pktinfo->data_rate <= ODM_RATEVHTSS2MCS9))
				max_spatial_stream = 2;
			else if ((pktinfo->data_rate >= ODM_RATEMCS16) &&
				 (pktinfo->data_rate <= ODM_RATEMCS23))
				max_spatial_stream = 3;
			else if ((pktinfo->data_rate >= ODM_RATEVHTSS3MCS0) &&
				 (pktinfo->data_rate <= ODM_RATEVHTSS3MCS9))
				max_spatial_stream = 3;
			else
				max_spatial_stream = 1;

			for (i = 0; i < max_spatial_stream; i++) {
				/*Don't use shift operation like "rx_evmX >>= 1"
				 *because the compilor of free build environment
				 *fill most significant bit to "zero" when doing
				 *shifting operation which may change a negative
				 *value to positive one, then the dbm value
				 *(which is supposed to be negative) is not
				 *correct anymore.
				 */

				EVM = phydm_get_odm_evm(i, pktinfo,
							phy_sta_rpt);
				evm_dbm = phydm_get_evm_dbm(i, EVM, phy_sta_rpt,
							    phy_info);
				phy_info->rx_mimo_signal_quality[i] = EVM;
				phy_info->rx_mimo_evm_dbm[i] = evm_dbm;
			}
		}

		num_ss = phydm_rate_to_num_ss(dm, pktinfo->data_rate);
		odm_parsing_cfo(dm, pktinfo, phy_sta_rpt->cfotail, num_ss);
	}

	/*UI BSS List signal strength(in percentage), make it good looking,
	 *from 0~100.
	 */
	/*It is assigned to the BSS List in GetValueFromBeaconOrProbeRsp().*/
	if (is_cck_rate) {
		phy_info->signal_strength = (u8)(
			odm_signal_scale_mapping(dm, pwdb_all)); /*pwdb_all;*/
	} else {
		if (rf_rx_num != 0) {
			/* 2015/01 Sean, use the best two RSSI only,
			 * suggested by Ynlin and ChenYu.
			 */
			if (rf_rx_num == 1)
				avg_rssi = best_rssi;
			else
				avg_rssi = (best_rssi + second_rssi) / 2;
			phy_info->signal_strength =
				(u8)(odm_signal_scale_mapping(dm, avg_rssi));
		}
	}
	dm->rx_pwdb_ave = dm->rx_pwdb_ave + phy_info->rx_pwdb_all;

	dm->dm_fat_table.antsel_rx_keep_0 = phy_sta_rpt->antidx_anta;
	dm->dm_fat_table.antsel_rx_keep_1 = phy_sta_rpt->antidx_antb;
	dm->dm_fat_table.antsel_rx_keep_2 = phy_sta_rpt->antidx_antc;
	dm->dm_fat_table.antsel_rx_keep_3 = phy_sta_rpt->antidx_antd;
}