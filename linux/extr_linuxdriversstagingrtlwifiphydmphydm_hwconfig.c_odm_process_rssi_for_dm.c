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
struct TYPE_4__ {int ofdm_pkt; int cck_pkt; scalar_t__ is_send_rssi; void* undecorated_smoothed_pwdb; void* undecorated_smoothed_ofdm; void* undecorated_smoothed_cck; } ;
struct rtl_sta_info {TYPE_2__ rssi_stat; } ;
struct TYPE_3__ {int /*<<< orphan*/  num_qry_beacon_pkt; } ;
struct phy_dm_struct {scalar_t__ rx_rate; TYPE_1__ phy_dbg_info; struct rtl_sta_info** odm_sta_info; } ;
struct dm_phy_status_info {int dummy; } ;
struct dm_per_pkt_info {size_t station_id; scalar_t__ data_rate; scalar_t__ is_packet_beacon; scalar_t__ is_packet_to_self; int /*<<< orphan*/  is_packet_match_bssid; } ;
typedef  void* s32 ;

/* Variables and functions */
 int /*<<< orphan*/  IS_STA_VALID (struct rtl_sta_info*) ; 
 size_t ODM_ASSOCIATE_ENTRY_NUM ; 
 int /*<<< orphan*/  ODM_COMP_RSSI_MONITOR ; 
 scalar_t__ ODM_RATE11M ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,void*,int,int) ; 
 scalar_t__ RA_RSSI_STATE_INIT ; 
 scalar_t__ RA_RSSI_STATE_SEND ; 
 void* phydm_process_rssi_cck (struct phy_dm_struct*,struct dm_phy_status_info*,struct rtl_sta_info*,void*) ; 
 void* phydm_process_rssi_ofdm (struct phy_dm_struct*,struct dm_phy_status_info*,struct rtl_sta_info*,void*) ; 
 void* phydm_process_rssi_pwdb (struct phy_dm_struct*,struct rtl_sta_info*,struct dm_per_pkt_info*,void*,void*) ; 

__attribute__((used)) static void odm_process_rssi_for_dm(struct phy_dm_struct *dm,
				    struct dm_phy_status_info *phy_info,
				    struct dm_per_pkt_info *pktinfo)
{
	s32 undecorated_smoothed_pwdb, undecorated_smoothed_cck,
		undecorated_smoothed_ofdm;
	u8 is_cck_rate = 0;
	u8 send_rssi_2_fw = 0;
	struct rtl_sta_info *entry;

	if (pktinfo->station_id >= ODM_ASSOCIATE_ENTRY_NUM)
		return;

	/* 2012/05/30 MH/Luke.Lee Add some description */
	/* In windows driver: AP/IBSS mode STA */
	entry = dm->odm_sta_info[pktinfo->station_id];

	if (!IS_STA_VALID(entry))
		return;

	{
		if ((!pktinfo->is_packet_match_bssid)) /*data frame only*/
			return;
	}

	if (pktinfo->is_packet_beacon)
		dm->phy_dbg_info.num_qry_beacon_pkt++;

	is_cck_rate = (pktinfo->data_rate <= ODM_RATE11M) ? true : false;
	dm->rx_rate = pktinfo->data_rate;

	/* --------------Statistic for antenna/path diversity---------------- */

	/* -----------------Smart Antenna Debug Message------------------ */

	undecorated_smoothed_cck = entry->rssi_stat.undecorated_smoothed_cck;
	undecorated_smoothed_ofdm = entry->rssi_stat.undecorated_smoothed_ofdm;
	undecorated_smoothed_pwdb = entry->rssi_stat.undecorated_smoothed_pwdb;

	if (pktinfo->is_packet_to_self || pktinfo->is_packet_beacon) {
		if (!is_cck_rate) /* ofdm rate */
			undecorated_smoothed_ofdm = phydm_process_rssi_ofdm(
				dm, phy_info, entry, undecorated_smoothed_ofdm);
		else
			undecorated_smoothed_cck = phydm_process_rssi_cck(
				dm, phy_info, entry, undecorated_smoothed_cck);

		undecorated_smoothed_pwdb = phydm_process_rssi_pwdb(
			dm, entry, pktinfo, undecorated_smoothed_ofdm,
			undecorated_smoothed_cck);

		if ((entry->rssi_stat.ofdm_pkt >= 1 ||
		     entry->rssi_stat.cck_pkt >= 5) &&
		    (entry->rssi_stat.is_send_rssi == RA_RSSI_STATE_INIT)) {
			send_rssi_2_fw = 1;
			entry->rssi_stat.is_send_rssi = RA_RSSI_STATE_SEND;
		}

		entry->rssi_stat.undecorated_smoothed_cck =
			undecorated_smoothed_cck;
		entry->rssi_stat.undecorated_smoothed_ofdm =
			undecorated_smoothed_ofdm;
		entry->rssi_stat.undecorated_smoothed_pwdb =
			undecorated_smoothed_pwdb;

		if (send_rssi_2_fw) { /* Trigger init rate by RSSI */

			if (entry->rssi_stat.ofdm_pkt != 0)
				entry->rssi_stat.undecorated_smoothed_pwdb =
					undecorated_smoothed_ofdm;

			ODM_RT_TRACE(
				dm, ODM_COMP_RSSI_MONITOR,
				"[Send to FW] PWDB = (( %d )), ofdm_pkt = (( %d )), cck_pkt = (( %d ))\n",
				undecorated_smoothed_pwdb,
				entry->rssi_stat.ofdm_pkt,
				entry->rssi_stat.cck_pkt);
		}
	}
}