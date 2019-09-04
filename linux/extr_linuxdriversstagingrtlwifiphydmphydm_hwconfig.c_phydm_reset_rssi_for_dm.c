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
typedef  size_t u8 ;
struct TYPE_2__ {int undecorated_smoothed_cck; int undecorated_smoothed_ofdm; int undecorated_smoothed_pwdb; scalar_t__ valid_bit; scalar_t__ packet_map; int /*<<< orphan*/  is_send_rssi; scalar_t__ cck_sum_power; scalar_t__ cck_pkt; scalar_t__ ofdm_pkt; } ;
struct rtl_sta_info {TYPE_1__ rssi_stat; } ;
struct phy_dm_struct {struct rtl_sta_info** odm_sta_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_STA_VALID (struct rtl_sta_info*) ; 
 int /*<<< orphan*/  ODM_COMP_RSSI_MONITOR ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct phy_dm_struct*,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  RA_RSSI_STATE_INIT ; 

void phydm_reset_rssi_for_dm(struct phy_dm_struct *dm, u8 station_id)
{
	struct rtl_sta_info *entry;

	entry = dm->odm_sta_info[station_id];

	if (!IS_STA_VALID(entry))
		return;

	ODM_RT_TRACE(dm, ODM_COMP_RSSI_MONITOR,
		     "Reset RSSI for macid = (( %d ))\n", station_id);

	entry->rssi_stat.undecorated_smoothed_cck = -1;
	entry->rssi_stat.undecorated_smoothed_ofdm = -1;
	entry->rssi_stat.undecorated_smoothed_pwdb = -1;
	entry->rssi_stat.ofdm_pkt = 0;
	entry->rssi_stat.cck_pkt = 0;
	entry->rssi_stat.cck_sum_power = 0;
	entry->rssi_stat.is_send_rssi = RA_RSSI_STATE_INIT;
	entry->rssi_stat.packet_map = 0;
	entry->rssi_stat.valid_bit = 0;
}