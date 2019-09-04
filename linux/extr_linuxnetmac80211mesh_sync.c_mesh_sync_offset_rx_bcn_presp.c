#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u16 ;
struct TYPE_9__ {int /*<<< orphan*/  addr; } ;
struct sta_info {TYPE_5__* mesh; TYPE_4__ sta; } ;
struct ieee802_11_elems {scalar_t__ mesh_config; scalar_t__ total_len; } ;
struct ieee80211_if_mesh {scalar_t__ mesh_sp_id; int /*<<< orphan*/  sync_offset_lock; scalar_t__ sync_offset_clockdrift_max; } ;
struct TYPE_6__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {struct ieee80211_local* local; TYPE_1__ u; } ;
struct ieee80211_rx_status {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  timestamp; } ;
struct TYPE_8__ {TYPE_2__ beacon; } ;
struct ieee80211_mgmt {TYPE_3__ u; int /*<<< orphan*/  sa; } ;
struct ieee80211_local {int dummy; } ;
typedef  scalar_t__ s64 ;
struct TYPE_10__ {scalar_t__ t_offset; scalar_t__ t_offset_setpoint; } ;

/* Variables and functions */
 scalar_t__ FCS_LEN ; 
 scalar_t__ IEEE80211_STYPE_BEACON ; 
 scalar_t__ IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET ; 
 scalar_t__ TOFFSET_MAXIMUM_ADJUSTMENT ; 
 scalar_t__ TOFFSET_SET_MARGIN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_STA_TOFFSET_KNOWN ; 
 int /*<<< orphan*/  clear_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ drv_get_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 scalar_t__ ieee80211_calculate_rx_timestamp (struct ieee80211_local*,struct ieee80211_rx_status*,scalar_t__,int) ; 
 scalar_t__ ieee80211_have_rx_timestamp (struct ieee80211_rx_status*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ mesh_peer_tbtt_adjusting (struct ieee802_11_elems*) ; 
 int /*<<< orphan*/  msync_dbg (struct ieee80211_sub_if_data*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  set_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct sta_info* sta_info_get (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_sta_flag (struct sta_info*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mesh_sync_offset_rx_bcn_presp(struct ieee80211_sub_if_data *sdata,
				   u16 stype,
				   struct ieee80211_mgmt *mgmt,
				   struct ieee802_11_elems *elems,
				   struct ieee80211_rx_status *rx_status)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct ieee80211_local *local = sdata->local;
	struct sta_info *sta;
	u64 t_t, t_r;

	WARN_ON(ifmsh->mesh_sp_id != IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET);

	/* standard mentions only beacons */
	if (stype != IEEE80211_STYPE_BEACON)
		return;

	/*
	 * Get time when timestamp field was received.  If we don't
	 * have rx timestamps, then use current tsf as an approximation.
	 * drv_get_tsf() must be called before entering the rcu-read
	 * section.
	 */
	if (ieee80211_have_rx_timestamp(rx_status))
		t_r = ieee80211_calculate_rx_timestamp(local, rx_status,
						       24 + 12 +
						       elems->total_len +
						       FCS_LEN,
						       24);
	else
		t_r = drv_get_tsf(local, sdata);

	rcu_read_lock();
	sta = sta_info_get(sdata, mgmt->sa);
	if (!sta)
		goto no_sync;

	/* check offset sync conditions (13.13.2.2.1)
	 *
	 * TODO also sync to
	 * dot11MeshNbrOffsetMaxNeighbor non-peer non-MBSS neighbors
	 */

	if (elems->mesh_config && mesh_peer_tbtt_adjusting(elems)) {
		msync_dbg(sdata, "STA %pM : is adjusting TBTT\n",
			  sta->sta.addr);
		goto no_sync;
	}

	/* Timing offset calculation (see 13.13.2.2.2) */
	t_t = le64_to_cpu(mgmt->u.beacon.timestamp);
	sta->mesh->t_offset = t_t - t_r;

	if (test_sta_flag(sta, WLAN_STA_TOFFSET_KNOWN)) {
		s64 t_clockdrift = sta->mesh->t_offset_setpoint - sta->mesh->t_offset;
		msync_dbg(sdata,
			  "STA %pM : t_offset=%lld, t_offset_setpoint=%lld, t_clockdrift=%lld\n",
			  sta->sta.addr, (long long) sta->mesh->t_offset,
			  (long long) sta->mesh->t_offset_setpoint,
			  (long long) t_clockdrift);

		if (t_clockdrift > TOFFSET_MAXIMUM_ADJUSTMENT ||
		    t_clockdrift < -TOFFSET_MAXIMUM_ADJUSTMENT) {
			msync_dbg(sdata,
				  "STA %pM : t_clockdrift=%lld too large, setpoint reset\n",
				  sta->sta.addr,
				  (long long) t_clockdrift);
			clear_sta_flag(sta, WLAN_STA_TOFFSET_KNOWN);
			goto no_sync;
		}

		spin_lock_bh(&ifmsh->sync_offset_lock);
		if (t_clockdrift > ifmsh->sync_offset_clockdrift_max)
			ifmsh->sync_offset_clockdrift_max = t_clockdrift;
		spin_unlock_bh(&ifmsh->sync_offset_lock);
	} else {
		sta->mesh->t_offset_setpoint = sta->mesh->t_offset - TOFFSET_SET_MARGIN;
		set_sta_flag(sta, WLAN_STA_TOFFSET_KNOWN);
		msync_dbg(sdata,
			  "STA %pM : offset was invalid, t_offset=%lld\n",
			  sta->sta.addr,
			  (long long) sta->mesh->t_offset);
	}

no_sync:
	rcu_read_unlock();
}