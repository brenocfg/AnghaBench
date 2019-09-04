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
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct rtl_sta_info {int dummy; } ;
struct ra_table {scalar_t__* link_tx_rate; } ;
struct TYPE_2__ {scalar_t__ is_stbc_pkt; scalar_t__ is_ldpc_pkt; } ;
struct dig_thres {int /*<<< orphan*/  cur_ig_value; } ;
struct phy_dm_struct {int is_linked; int* band_width; scalar_t__ rx_rate; int rssi_a; int rssi_b; int rssi_c; int rssi_d; size_t* platform2phydm_macid_table; size_t number_linked_client; int support_ic_type; int /*<<< orphan*/  noisy_decision; int /*<<< orphan*/  rssi_min; TYPE_1__ phy_dbg_info; int /*<<< orphan*/  traffic_load; int /*<<< orphan*/  total_tp; int /*<<< orphan*/  rx_tp; int /*<<< orphan*/  tx_tp; struct rtl_sta_info** odm_sta_info; int /*<<< orphan*/ * ofdm_agc_idx; int /*<<< orphan*/  cck_vga_idx; int /*<<< orphan*/  cck_lna_idx; int /*<<< orphan*/ * channel; int /*<<< orphan*/  curr_station_id; int /*<<< orphan*/  phydm_sys_up_time; struct ra_table dm_ra_table; struct dig_thres dm_dig_table; } ;
struct false_alarm_stat {int /*<<< orphan*/  cnt_sb_search_fail; int /*<<< orphan*/  cnt_fast_fsync; int /*<<< orphan*/  cnt_mcs_fail; int /*<<< orphan*/  cnt_crc8_fail; int /*<<< orphan*/  cnt_rate_illegal; int /*<<< orphan*/  cnt_parity_fail; int /*<<< orphan*/  cnt_all; int /*<<< orphan*/  cnt_ofdm_fail; int /*<<< orphan*/  cnt_cck_fail; int /*<<< orphan*/  cnt_cca_all; int /*<<< orphan*/  cnt_ofdm_cca; int /*<<< orphan*/  cnt_cck_cca; } ;
struct cfo_tracking {scalar_t__ crystal_cap; scalar_t__ def_x_cap; int /*<<< orphan*/  CFO_ave_pre; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IS_STA_VALID (struct rtl_sta_info*) ; 
 size_t ODM_ASSOCIATE_ENTRY_NUM ; 
 int /*<<< orphan*/  ODM_COMP_COMMON ; 
 int ODM_IC_11N_SERIES ; 
 scalar_t__ ODM_RATE11M ; 
 int ODM_RTL8822B ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  PHYDM_CFOTRACK ; 
 int /*<<< orphan*/  PHYDM_FALSEALMCNT ; 
 int /*<<< orphan*/  phydm_get_condition_number_8822B (struct phy_dm_struct*) ; 
 scalar_t__ phydm_get_structure (struct phy_dm_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phydm_print_rate (struct phy_dm_struct*,scalar_t__,int /*<<< orphan*/ ) ; 

void phydm_basic_dbg_message(void *dm_void)
{
	struct phy_dm_struct *dm = (struct phy_dm_struct *)dm_void;
	struct false_alarm_stat *false_alm_cnt =
		(struct false_alarm_stat *)phydm_get_structure(
			dm, PHYDM_FALSEALMCNT);
	struct cfo_tracking *cfo_track =
		(struct cfo_tracking *)phydm_get_structure(dm, PHYDM_CFOTRACK);
	struct dig_thres *dig_tab = &dm->dm_dig_table;
	struct ra_table *ra_tab = &dm->dm_ra_table;
	u16 macid, phydm_macid, client_cnt = 0;
	struct rtl_sta_info *entry;
	s32 tmp_val = 0;
	u8 tmp_val_u1 = 0;

	ODM_RT_TRACE(dm, ODM_COMP_COMMON,
		     "[PHYDM Common MSG] System up time: ((%d sec))----->\n",
		     dm->phydm_sys_up_time);

	if (dm->is_linked) {
		ODM_RT_TRACE(dm, ODM_COMP_COMMON,
			     "ID=%d, BW=((%d)), CH=((%d))\n",
			     dm->curr_station_id, 20 << *dm->band_width,
			     *dm->channel);

		/*Print RX rate*/
		if (dm->rx_rate <= ODM_RATE11M)
			ODM_RT_TRACE(
				dm, ODM_COMP_COMMON,
				"[CCK AGC Report] LNA_idx = 0x%x, VGA_idx = 0x%x\n",
				dm->cck_lna_idx, dm->cck_vga_idx);
		else
			ODM_RT_TRACE(
				dm, ODM_COMP_COMMON,
				"[OFDM AGC Report] { 0x%x, 0x%x, 0x%x, 0x%x }\n",
				dm->ofdm_agc_idx[0], dm->ofdm_agc_idx[1],
				dm->ofdm_agc_idx[2], dm->ofdm_agc_idx[3]);

		ODM_RT_TRACE(dm, ODM_COMP_COMMON,
			     "RSSI: { %d,  %d,  %d,  %d },    rx_rate:",
			     (dm->rssi_a == 0xff) ? 0 : dm->rssi_a,
			     (dm->rssi_b == 0xff) ? 0 : dm->rssi_b,
			     (dm->rssi_c == 0xff) ? 0 : dm->rssi_c,
			     (dm->rssi_d == 0xff) ? 0 : dm->rssi_d);

		phydm_print_rate(dm, dm->rx_rate, ODM_COMP_COMMON);

		/*Print TX rate*/
		for (macid = 0; macid < ODM_ASSOCIATE_ENTRY_NUM; macid++) {
			entry = dm->odm_sta_info[macid];
			if (!IS_STA_VALID(entry))
				continue;

			phydm_macid = (dm->platform2phydm_macid_table[macid]);
			ODM_RT_TRACE(dm, ODM_COMP_COMMON, "TXRate [%d]:",
				     macid);
			phydm_print_rate(dm, ra_tab->link_tx_rate[macid],
					 ODM_COMP_COMMON);

			client_cnt++;

			if (client_cnt == dm->number_linked_client)
				break;
		}

		ODM_RT_TRACE(
			dm, ODM_COMP_COMMON,
			"TP { TX, RX, total} = {%d, %d, %d }Mbps, traffic_load = (%d))\n",
			dm->tx_tp, dm->rx_tp, dm->total_tp, dm->traffic_load);

		tmp_val_u1 =
			(cfo_track->crystal_cap > cfo_track->def_x_cap) ?
				(cfo_track->crystal_cap -
				 cfo_track->def_x_cap) :
				(cfo_track->def_x_cap - cfo_track->crystal_cap);
		ODM_RT_TRACE(
			dm, ODM_COMP_COMMON,
			"CFO_avg = ((%d kHz)) , CrystalCap_tracking = ((%s%d))\n",
			cfo_track->CFO_ave_pre,
			((cfo_track->crystal_cap > cfo_track->def_x_cap) ? "+" :
									   "-"),
			tmp_val_u1);

		/* Condition number */
		if (dm->support_ic_type == ODM_RTL8822B) {
			tmp_val = phydm_get_condition_number_8822B(dm);
			ODM_RT_TRACE(dm, ODM_COMP_COMMON,
				     "Condition number = ((%d))\n", tmp_val);
		}

		/*STBC or LDPC pkt*/
		ODM_RT_TRACE(dm, ODM_COMP_COMMON, "LDPC = %s, STBC = %s\n",
			     (dm->phy_dbg_info.is_ldpc_pkt) ? "Y" : "N",
			     (dm->phy_dbg_info.is_stbc_pkt) ? "Y" : "N");
	} else {
		ODM_RT_TRACE(dm, ODM_COMP_COMMON, "No Link !!!\n");
	}

	ODM_RT_TRACE(dm, ODM_COMP_COMMON,
		     "[CCA Cnt] {CCK, OFDM, Total} = {%d, %d, %d}\n",
		     false_alm_cnt->cnt_cck_cca, false_alm_cnt->cnt_ofdm_cca,
		     false_alm_cnt->cnt_cca_all);

	ODM_RT_TRACE(dm, ODM_COMP_COMMON,
		     "[FA Cnt] {CCK, OFDM, Total} = {%d, %d, %d}\n",
		     false_alm_cnt->cnt_cck_fail, false_alm_cnt->cnt_ofdm_fail,
		     false_alm_cnt->cnt_all);

	if (dm->support_ic_type & ODM_IC_11N_SERIES)
		ODM_RT_TRACE(
			dm, ODM_COMP_COMMON,
			"[OFDM FA Detail] Parity_Fail = (( %d )), Rate_Illegal = (( %d )), CRC8_fail = (( %d )), Mcs_fail = (( %d )), Fast_Fsync = (( %d )), SB_Search_fail = (( %d ))\n",
			false_alm_cnt->cnt_parity_fail,
			false_alm_cnt->cnt_rate_illegal,
			false_alm_cnt->cnt_crc8_fail,
			false_alm_cnt->cnt_mcs_fail,
			false_alm_cnt->cnt_fast_fsync,
			false_alm_cnt->cnt_sb_search_fail);

	ODM_RT_TRACE(
		dm, ODM_COMP_COMMON,
		"is_linked = %d, Num_client = %d, rssi_min = %d, current_igi = 0x%x, bNoisy=%d\n\n",
		dm->is_linked, dm->number_linked_client, dm->rssi_min,
		dig_tab->cur_ig_value, dm->noisy_decision);
}