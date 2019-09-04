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
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_4__ {size_t undecorated_smoothed_pwdb; } ;
struct rtl_sta_info {TYPE_2__ rssi_stat; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_qry_beacon_pkt; } ;
struct phy_dm_struct {size_t* accumulate_pwdb; scalar_t__ rssi_a; scalar_t__ rssi_b; scalar_t__ rssi_c; scalar_t__ rssi_d; int /*<<< orphan*/  rx_rate; TYPE_1__ phy_dbg_info; struct rtl_sta_info** odm_sta_info; } ;
struct dm_phy_status_info {scalar_t__* rx_mimo_signal_strength; int rx_count; size_t rx_pwdb_all; } ;
struct dm_per_pkt_info {size_t station_id; int /*<<< orphan*/  data_rate; scalar_t__ is_packet_beacon; scalar_t__ is_packet_to_self; int /*<<< orphan*/  is_packet_match_bssid; } ;
typedef  size_t s32 ;
typedef  int rssi_linear ;

/* Variables and functions */
 int /*<<< orphan*/  IS_STA_VALID (struct rtl_sta_info*) ; 
 size_t ODM_ASSOCIATE_ENTRY_NUM ; 
 size_t ODM_RF_PATH_A ; 
 size_t ODM_RF_PATH_B ; 
 size_t ODM_RF_PATH_C ; 
 size_t ODM_RF_PATH_D ; 
 size_t ODM_RF_PATH_MAX_JAGUAR ; 
 int odm_convert_to_db (int) ; 
 scalar_t__ odm_convert_to_linear (scalar_t__) ; 

__attribute__((used)) static void
phydm_process_rssi_for_dm_new_type(struct phy_dm_struct *dm,
				   struct dm_phy_status_info *phy_info,
				   struct dm_per_pkt_info *pktinfo)
{
	s32 undecorated_smoothed_pwdb, accumulate_pwdb;
	u32 rssi_ave;
	u8 i;
	struct rtl_sta_info *entry;
	u8 scaling_factor = 4;

	if (pktinfo->station_id >= ODM_ASSOCIATE_ENTRY_NUM)
		return;

	entry = dm->odm_sta_info[pktinfo->station_id];

	if (!IS_STA_VALID(entry))
		return;

	if ((!pktinfo->is_packet_match_bssid)) /*data frame only*/
		return;

	if (pktinfo->is_packet_beacon)
		dm->phy_dbg_info.num_qry_beacon_pkt++;

	if (pktinfo->is_packet_to_self || pktinfo->is_packet_beacon) {
		u32 rssi_linear = 0;

		dm->rx_rate = pktinfo->data_rate;
		undecorated_smoothed_pwdb =
			entry->rssi_stat.undecorated_smoothed_pwdb;
		accumulate_pwdb = dm->accumulate_pwdb[pktinfo->station_id];
		dm->rssi_a = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_A];
		dm->rssi_b = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_B];
		dm->rssi_c = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_C];
		dm->rssi_d = phy_info->rx_mimo_signal_strength[ODM_RF_PATH_D];

		for (i = ODM_RF_PATH_A; i < ODM_RF_PATH_MAX_JAGUAR; i++) {
			if (phy_info->rx_mimo_signal_strength[i] != 0)
				rssi_linear += odm_convert_to_linear(
					phy_info->rx_mimo_signal_strength[i]);
		}

		switch (phy_info->rx_count + 1) {
		case 2:
			rssi_linear = (rssi_linear >> 1);
			break;
		case 3:
			/* rssi_linear/3 ~ rssi_linear*11/32 */
			rssi_linear = ((rssi_linear) + (rssi_linear << 1) +
				       (rssi_linear << 3)) >>
				      5;
			break;
		case 4:
			rssi_linear = (rssi_linear >> 2);
			break;
		}
		rssi_ave = odm_convert_to_db(rssi_linear);

		if (undecorated_smoothed_pwdb <= 0) {
			accumulate_pwdb =
				(phy_info->rx_pwdb_all << scaling_factor);
			undecorated_smoothed_pwdb = phy_info->rx_pwdb_all;
		} else {
			accumulate_pwdb = accumulate_pwdb -
					  (accumulate_pwdb >> scaling_factor) +
					  rssi_ave;
			undecorated_smoothed_pwdb =
				(accumulate_pwdb +
				 (1 << (scaling_factor - 1))) >>
				scaling_factor;
		}

		entry->rssi_stat.undecorated_smoothed_pwdb =
			undecorated_smoothed_pwdb;
		dm->accumulate_pwdb[pktinfo->station_id] = accumulate_pwdb;
	}
}