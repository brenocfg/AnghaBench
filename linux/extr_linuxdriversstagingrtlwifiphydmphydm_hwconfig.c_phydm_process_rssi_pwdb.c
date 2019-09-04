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
typedef  int u32 ;
struct TYPE_2__ {int ofdm_pkt; int valid_bit; } ;
struct rtl_sta_info {TYPE_1__ rssi_stat; } ;
struct phy_dm_struct {int dummy; } ;
struct dm_per_pkt_info {int /*<<< orphan*/  station_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_COMP_RSSI_MONITOR ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static u32 phydm_process_rssi_pwdb(struct phy_dm_struct *dm,
				   struct rtl_sta_info *entry,
				   struct dm_per_pkt_info *pktinfo,
				   u32 undecorated_smoothed_ofdm,
				   u32 undecorated_smoothed_cck)
{
	u32 weighting = 0, undecorated_smoothed_pwdb;
	/* 2011.07.28 LukeLee: modified to prevent unstable CCK RSSI */

	if (entry->rssi_stat.ofdm_pkt ==
	    64) { /* speed up when all packets are OFDM*/
		undecorated_smoothed_pwdb = undecorated_smoothed_ofdm;
		ODM_RT_TRACE(dm, ODM_COMP_RSSI_MONITOR,
			     "PWDB_0[%d] = (( %d ))\n", pktinfo->station_id,
			     undecorated_smoothed_cck);
	} else {
		if (entry->rssi_stat.valid_bit < 64)
			entry->rssi_stat.valid_bit++;

		if (entry->rssi_stat.valid_bit == 64) {
			weighting = ((entry->rssi_stat.ofdm_pkt) > 4) ?
					    64 :
					    (entry->rssi_stat.ofdm_pkt << 4);
			undecorated_smoothed_pwdb =
				(weighting * undecorated_smoothed_ofdm +
				 (64 - weighting) * undecorated_smoothed_cck) >>
				6;
			ODM_RT_TRACE(dm, ODM_COMP_RSSI_MONITOR,
				     "PWDB_1[%d] = (( %d )), W = (( %d ))\n",
				     pktinfo->station_id,
				     undecorated_smoothed_cck, weighting);
		} else {
			if (entry->rssi_stat.valid_bit != 0)
				undecorated_smoothed_pwdb =
					(entry->rssi_stat.ofdm_pkt *
						 undecorated_smoothed_ofdm +
					 (entry->rssi_stat.valid_bit -
					  entry->rssi_stat.ofdm_pkt) *
						 undecorated_smoothed_cck) /
					entry->rssi_stat.valid_bit;
			else
				undecorated_smoothed_pwdb = 0;

			ODM_RT_TRACE(
				dm, ODM_COMP_RSSI_MONITOR,
				"PWDB_2[%d] = (( %d )), ofdm_pkt = (( %d )), Valid_Bit = (( %d ))\n",
				pktinfo->station_id, undecorated_smoothed_cck,
				entry->rssi_stat.ofdm_pkt,
				entry->rssi_stat.valid_bit);
		}
	}

	return undecorated_smoothed_pwdb;
}