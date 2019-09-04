#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {int enable_beacon; int /*<<< orphan*/  ht_operation_mode; } ;
struct TYPE_8__ {TYPE_3__ bss_conf; } ;
struct TYPE_6__ {int /*<<< orphan*/  ht_opmode; } ;
struct ieee80211_if_mesh {TYPE_2__ mshcfg; int /*<<< orphan*/  wrkq_flags; scalar_t__ sync_offset_clockdrift_max; int /*<<< orphan*/  mesh_sp_id; int /*<<< orphan*/  sync_ops; scalar_t__ mesh_cc_id; } ;
struct TYPE_5__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {int /*<<< orphan*/  dev; TYPE_4__ vif; int /*<<< orphan*/  work; struct ieee80211_local* local; TYPE_1__ u; } ;
struct ieee80211_local {int /*<<< orphan*/  hw; int /*<<< orphan*/  iff_allmultis; int /*<<< orphan*/  fif_other_bss; } ;

/* Variables and functions */
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON ; 
 int BSS_CHANGED_BEACON_ENABLED ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_HT ; 
 int BSS_CHANGED_MCAST_RATE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MESH_WORK_HOUSEKEEPING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  ieee80211_configure_filter (struct ieee80211_local*) ; 
 scalar_t__ ieee80211_mesh_build_beacon (struct ieee80211_if_mesh*) ; 
 int /*<<< orphan*/  ieee80211_mesh_root_setup (struct ieee80211_if_mesh*) ; 
 int /*<<< orphan*/  ieee80211_mesh_sync_ops_get (int /*<<< orphan*/ ) ; 
 int ieee80211_mps_local_status_update (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_queue_work (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_recalc_dtim (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_stop_mesh (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ieee80211_start_mesh(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct ieee80211_local *local = sdata->local;
	u32 changed = BSS_CHANGED_BEACON |
		      BSS_CHANGED_BEACON_ENABLED |
		      BSS_CHANGED_HT |
		      BSS_CHANGED_BASIC_RATES |
		      BSS_CHANGED_BEACON_INT |
		      BSS_CHANGED_MCAST_RATE;

	local->fif_other_bss++;
	/* mesh ifaces must set allmulti to forward mcast traffic */
	atomic_inc(&local->iff_allmultis);
	ieee80211_configure_filter(local);

	ifmsh->mesh_cc_id = 0;	/* Disabled */
	/* register sync ops from extensible synchronization framework */
	ifmsh->sync_ops = ieee80211_mesh_sync_ops_get(ifmsh->mesh_sp_id);
	ifmsh->sync_offset_clockdrift_max = 0;
	set_bit(MESH_WORK_HOUSEKEEPING, &ifmsh->wrkq_flags);
	ieee80211_mesh_root_setup(ifmsh);
	ieee80211_queue_work(&local->hw, &sdata->work);
	sdata->vif.bss_conf.ht_operation_mode =
				ifmsh->mshcfg.ht_opmode;
	sdata->vif.bss_conf.enable_beacon = true;

	changed |= ieee80211_mps_local_status_update(sdata);

	if (ieee80211_mesh_build_beacon(ifmsh)) {
		ieee80211_stop_mesh(sdata);
		return -ENOMEM;
	}

	ieee80211_recalc_dtim(local, sdata);
	ieee80211_bss_info_change_notify(sdata, changed);

	netif_carrier_on(sdata->dev);
	return 0;
}