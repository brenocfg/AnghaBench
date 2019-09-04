#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct phy_status_rpt_8192cd {int cck_agc_rpt_ofdm_cfosho_a; int* path_rxsnr; int cck_sig_qual_ofdm_pwdb_all; int /*<<< orphan*/  path_cfotail; int /*<<< orphan*/ * stream_rxevm; TYPE_1__* path_agc; } ;
struct TYPE_4__ {scalar_t__* rx_snr_db; int /*<<< orphan*/  num_qry_phy_status_ofdm; int /*<<< orphan*/  num_qry_phy_status_cck; } ;
struct phy_dm_struct {int support_ic_type; int board_type; int cck_lna_idx; int cck_vga_idx; int rf_path_rx_enable; int* ofdm_agc_idx; scalar_t__ support_platform; int patch_id; TYPE_2__ phy_dbg_info; scalar_t__ ext_lna_gain; int /*<<< orphan*/  curr_station_id; } ;
struct dm_phy_status_info {int* rx_mimo_signal_quality; int rx_pwdb_all; int bt_rx_rssi_percentage; int signal_quality; int* rx_mimo_signal_strength; int signal_strength; void* recv_signal_power; void* rx_power; scalar_t__* rx_snr; void** rx_pwr; } ;
struct dm_per_pkt_info {scalar_t__ data_rate; scalar_t__ is_to_self; int /*<<< orphan*/  station_id; } ;
typedef  void* s8 ;
typedef  scalar_t__ s32 ;
struct TYPE_3__ {int gain; } ;

/* Variables and functions */
 int BIT (int) ; 
 int ODM_BOARD_EXT_LNA ; 
 int /*<<< orphan*/  ODM_COMP_RSSI_MONITOR ; 
 scalar_t__ ODM_RATE11M ; 
 scalar_t__ ODM_RATEMCS15 ; 
 scalar_t__ ODM_RATEMCS8 ; 
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 
 int ODM_RF_PATH_MAX ; 
 int ODM_RTL8703B ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,scalar_t__,int,int,void*) ; 
 scalar_t__ ODM_WIN ; 
 int odm_evm_db_to_percentage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  odm_parsing_cfo (struct phy_dm_struct*,struct dm_per_pkt_info*,int /*<<< orphan*/ ,int) ; 
 int odm_query_rx_pwr_percentage (void*) ; 
 scalar_t__ odm_signal_scale_mapping (struct phy_dm_struct*,int) ; 
 int phydm_get_signal_quality_8192 (struct dm_phy_status_info*,struct phy_dm_struct*,struct phy_status_rpt_8192cd*) ; 
 int phydm_rate_to_num_ss (struct phy_dm_struct*,scalar_t__) ; 

__attribute__((used)) static void odm_rx_phy_status92c_series_parsing(
	struct phy_dm_struct *dm, struct dm_phy_status_info *phy_info,
	u8 *phy_status, struct dm_per_pkt_info *pktinfo)
{
	u8 i, max_spatial_stream;
	s8 rx_pwr[4], rx_pwr_all = 0;
	u8 EVM, pwdb_all = 0, pwdb_all_bt;
	u8 RSSI, total_rssi = 0;
	bool is_cck_rate = false;
	u8 rf_rx_num = 0;
	u8 LNA_idx = 0;
	u8 VGA_idx = 0;
	u8 cck_agc_rpt;
	u8 num_ss;
	struct phy_status_rpt_8192cd *phy_sta_rpt =
		(struct phy_status_rpt_8192cd *)phy_status;

	is_cck_rate = (pktinfo->data_rate <= ODM_RATE11M) ? true : false;

	if (pktinfo->is_to_self)
		dm->curr_station_id = pktinfo->station_id;

	phy_info->rx_mimo_signal_quality[ODM_RF_PATH_A] = -1;
	phy_info->rx_mimo_signal_quality[ODM_RF_PATH_B] = -1;

	if (is_cck_rate) {
		dm->phy_dbg_info.num_qry_phy_status_cck++;
		cck_agc_rpt = phy_sta_rpt->cck_agc_rpt_ofdm_cfosho_a;

		if (dm->support_ic_type & (ODM_RTL8703B)) {
		} else { /*3 bit LNA*/

			LNA_idx = ((cck_agc_rpt & 0xE0) >> 5);
			VGA_idx = (cck_agc_rpt & 0x1F);
		}

		ODM_RT_TRACE(
			dm, ODM_COMP_RSSI_MONITOR,
			"ext_lna_gain (( %d )), LNA_idx: (( 0x%x )), VGA_idx: (( 0x%x )), rx_pwr_all: (( %d ))\n",
			dm->ext_lna_gain, LNA_idx, VGA_idx, rx_pwr_all);

		if (dm->board_type & ODM_BOARD_EXT_LNA)
			rx_pwr_all -= dm->ext_lna_gain;

		pwdb_all = odm_query_rx_pwr_percentage(rx_pwr_all);

		if (pktinfo->is_to_self) {
			dm->cck_lna_idx = LNA_idx;
			dm->cck_vga_idx = VGA_idx;
		}
		phy_info->rx_pwdb_all = pwdb_all;

		phy_info->bt_rx_rssi_percentage = pwdb_all;
		phy_info->recv_signal_power = rx_pwr_all;
		/* (3) Get Signal Quality (EVM) */
		{
			u8 sq;

			sq = phydm_get_signal_quality_8192(phy_info, dm,
							   phy_sta_rpt);
			phy_info->signal_quality = sq;
			phy_info->rx_mimo_signal_quality[ODM_RF_PATH_A] = sq;
			phy_info->rx_mimo_signal_quality[ODM_RF_PATH_B] = -1;
		}

		for (i = ODM_RF_PATH_A; i < ODM_RF_PATH_MAX; i++) {
			if (i == 0)
				phy_info->rx_mimo_signal_strength[0] = pwdb_all;
			else
				phy_info->rx_mimo_signal_strength[1] = 0;
		}
	} else { /* 2 is OFDM rate */
		dm->phy_dbg_info.num_qry_phy_status_ofdm++;

		/*  */
		/* (1)Get RSSI for HT rate */
		/*  */

		for (i = ODM_RF_PATH_A; i < ODM_RF_PATH_MAX; i++) {
			/* 2008/01/30 MH we will judge RF RX path now. */
			if (dm->rf_path_rx_enable & BIT(i))
				rf_rx_num++;
			/* else */
			/* continue; */

			rx_pwr[i] =
				((phy_sta_rpt->path_agc[i].gain & 0x3F) * 2) -
				110;

			if (pktinfo->is_to_self) {
				dm->ofdm_agc_idx[i] =
					(phy_sta_rpt->path_agc[i].gain & 0x3F);
				/**/
			}

			phy_info->rx_pwr[i] = rx_pwr[i];

			/* Translate DBM to percentage. */
			RSSI = odm_query_rx_pwr_percentage(rx_pwr[i]);
			total_rssi += RSSI;

			phy_info->rx_mimo_signal_strength[i] = (u8)RSSI;

			/* Get Rx snr value in DB */
			dm->phy_dbg_info.rx_snr_db[i] =
				(s32)(phy_sta_rpt->path_rxsnr[i] / 2);
			phy_info->rx_snr[i] = dm->phy_dbg_info.rx_snr_db[i];

			/* Record Signal Strength for next packet */
			/* if(pktinfo->is_packet_match_bssid) */
			{
			}
		}

		/*  */
		/* (2)PWDB, Average PWDB calcuated by hardware (for RA) */
		/*  */
		rx_pwr_all = (((phy_sta_rpt->cck_sig_qual_ofdm_pwdb_all) >> 1) &
			      0x7f) -
			     110;

		pwdb_all = odm_query_rx_pwr_percentage(rx_pwr_all);
		pwdb_all_bt = pwdb_all;

		phy_info->rx_pwdb_all = pwdb_all;
		phy_info->bt_rx_rssi_percentage = pwdb_all_bt;
		phy_info->rx_power = rx_pwr_all;
		phy_info->recv_signal_power = rx_pwr_all;

		if ((dm->support_platform == ODM_WIN) && (dm->patch_id == 19)) {
			/* do nothing */
		} else if ((dm->support_platform == ODM_WIN) &&
			   (dm->patch_id == 25)) {
			/* do nothing */
		} else { /* mgnt_info->customer_id != RT_CID_819X_LENOVO */
			/*  */
			/* (3)EVM of HT rate */
			/*  */
			if (pktinfo->data_rate >= ODM_RATEMCS8 &&
			    pktinfo->data_rate <= ODM_RATEMCS15) {
				/* both spatial stream make sense */
				max_spatial_stream = 2;
			} else {
				/* only spatial stream 1 makes sense */
				max_spatial_stream = 1;
			}

			for (i = 0; i < max_spatial_stream; i++) {
				/*Don't use shift operation like "rx_evmX >>= 1"
				 *because the compilor of free build environment
				 *fill most significant bit to "zero" when doing
				 *shifting operation which may change a negative
				 *value to positive one, then the dbm value
				 *(which is supposed to be negative)  is not
				 *correct anymore.
				 */
				EVM = odm_evm_db_to_percentage(
					(phy_sta_rpt
						 ->stream_rxevm[i])); /* dbm */

				/* Fill value in RFD, Get the first spatial
				 * stream only
				 */
				if (i == ODM_RF_PATH_A)
					phy_info->signal_quality =
						(u8)(EVM & 0xff);
				phy_info->rx_mimo_signal_quality[i] =
					(u8)(EVM & 0xff);
			}
		}

		num_ss = phydm_rate_to_num_ss(dm, pktinfo->data_rate);
		odm_parsing_cfo(dm, pktinfo, phy_sta_rpt->path_cfotail, num_ss);
	}
	/* UI BSS List signal strength(in percentage), make it good looking,
	 * from 0~100.
	 */
	/* It is assigned to the BSS List in GetValueFromBeaconOrProbeRsp(). */
	if (is_cck_rate) {
		phy_info->signal_strength = (u8)(
			odm_signal_scale_mapping(dm, pwdb_all)); /*pwdb_all;*/
	} else {
		if (rf_rx_num != 0) {
			phy_info->signal_strength =
				(u8)(odm_signal_scale_mapping(dm, total_rssi /=
								  rf_rx_num));
		}
	}

	/* For 92C/92D HW (Hybrid) Antenna Diversity */
}