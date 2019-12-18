#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_12__ {int /*<<< orphan*/  addr; } ;
struct sta_info {int /*<<< orphan*/  debugfs_dir; TYPE_6__ sta; int /*<<< orphan*/  driver_buffered_tids; struct ieee80211_sub_if_data* sdata; struct ieee80211_local* local; } ;
struct TYPE_7__ {struct dentry* subdir_stations; } ;
struct ieee80211_sub_if_data {TYPE_1__ debugfs; } ;
struct TYPE_9__ {int /*<<< orphan*/  wiphy; } ;
struct ieee80211_local {TYPE_3__ hw; TYPE_2__* ops; } ;
struct dentry {int dummy; } ;
typedef  int /*<<< orphan*/  mac ;
struct TYPE_11__ {int /*<<< orphan*/  fragments; int /*<<< orphan*/  num_duplicates; } ;
struct TYPE_10__ {int /*<<< orphan*/  filtered; } ;
struct TYPE_8__ {scalar_t__ wake_tx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUGFS_ADD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUGFS_ADD_COUNTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ETH_ALEN ; 
 int /*<<< orphan*/  NL80211_EXT_FEATURE_AIRTIME_FAIRNESS ; 
 int /*<<< orphan*/  agg_status ; 
 int /*<<< orphan*/  aid ; 
 int /*<<< orphan*/  airtime ; 
 int /*<<< orphan*/  aqm ; 
 int /*<<< orphan*/  debugfs_create_dir (int /*<<< orphan*/ *,struct dentry*) ; 
 int /*<<< orphan*/  debugfs_create_x32 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugfs_create_x64 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv_sta_add_debugfs (struct ieee80211_local*,struct ieee80211_sub_if_data*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  he_capa ; 
 int /*<<< orphan*/  ht_capa ; 
 int /*<<< orphan*/  last_seq_ctrl ; 
 int /*<<< orphan*/  num_ps_buf_frames ; 
 int /*<<< orphan*/  rx_duplicates ; 
 int /*<<< orphan*/  rx_fragments ; 
 TYPE_5__ rx_stats ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__ status_stats ; 
 int /*<<< orphan*/  tx_filtered ; 
 int /*<<< orphan*/  vht_capa ; 
 scalar_t__ wiphy_ext_feature_isset (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ieee80211_sta_debugfs_add(struct sta_info *sta)
{
	struct ieee80211_local *local = sta->local;
	struct ieee80211_sub_if_data *sdata = sta->sdata;
	struct dentry *stations_dir = sta->sdata->debugfs.subdir_stations;
	u8 mac[3*ETH_ALEN];

	if (!stations_dir)
		return;

	snprintf(mac, sizeof(mac), "%pM", sta->sta.addr);

	/*
	 * This might fail due to a race condition:
	 * When mac80211 unlinks a station, the debugfs entries
	 * remain, but it is already possible to link a new
	 * station with the same address which triggers adding
	 * it to debugfs; therefore, if the old station isn't
	 * destroyed quickly enough the old station's debugfs
	 * dir might still be around.
	 */
	sta->debugfs_dir = debugfs_create_dir(mac, stations_dir);

	DEBUGFS_ADD(flags);
	DEBUGFS_ADD(aid);
	DEBUGFS_ADD(num_ps_buf_frames);
	DEBUGFS_ADD(last_seq_ctrl);
	DEBUGFS_ADD(agg_status);
	DEBUGFS_ADD(ht_capa);
	DEBUGFS_ADD(vht_capa);
	DEBUGFS_ADD(he_capa);

	DEBUGFS_ADD_COUNTER(rx_duplicates, rx_stats.num_duplicates);
	DEBUGFS_ADD_COUNTER(rx_fragments, rx_stats.fragments);
	DEBUGFS_ADD_COUNTER(tx_filtered, status_stats.filtered);

	if (local->ops->wake_tx_queue)
		DEBUGFS_ADD(aqm);

	if (wiphy_ext_feature_isset(local->hw.wiphy,
				    NL80211_EXT_FEATURE_AIRTIME_FAIRNESS))
		DEBUGFS_ADD(airtime);

	if (sizeof(sta->driver_buffered_tids) == sizeof(u32))
		debugfs_create_x32("driver_buffered_tids", 0400,
				   sta->debugfs_dir,
				   (u32 *)&sta->driver_buffered_tids);
	else
		debugfs_create_x64("driver_buffered_tids", 0400,
				   sta->debugfs_dir,
				   (u64 *)&sta->driver_buffered_tids);

	drv_sta_add_debugfs(local, sdata, &sta->sta, sta->debugfs_dir);
}