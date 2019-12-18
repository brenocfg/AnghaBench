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
struct TYPE_9__ {int /*<<< orphan*/  bc_buf; } ;
struct ieee80211_if_mesh {scalar_t__ mbss_changed; scalar_t__ wrkq_flags; int /*<<< orphan*/  mesh_path_timer; int /*<<< orphan*/  mesh_path_root_timer; int /*<<< orphan*/  housekeeping_timer; TYPE_4__ ps; int /*<<< orphan*/  beacon; scalar_t__ mesh_id_len; } ;
struct TYPE_10__ {struct ieee80211_if_mesh mesh; } ;
struct TYPE_8__ {int /*<<< orphan*/  mtx; } ;
struct TYPE_6__ {int enable_beacon; } ;
struct TYPE_7__ {TYPE_1__ bss_conf; } ;
struct ieee80211_sub_if_data {TYPE_5__ u; TYPE_3__ wdev; int /*<<< orphan*/  state; TYPE_2__ vif; int /*<<< orphan*/  dev; struct ieee80211_local* local; } ;
struct ieee80211_local {int /*<<< orphan*/  iff_allmultis; int /*<<< orphan*/  fif_other_bss; int /*<<< orphan*/  total_ps_buffered; } ;
struct beacon_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSS_CHANGED_BEACON_ENABLED ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDATA_STATE_OFFCHANNEL_BEACON_STOPPED ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_bss_info_change_notify (struct ieee80211_sub_if_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_configure_filter (struct ieee80211_local*) ; 
 int /*<<< orphan*/  ieee80211_free_keys (struct ieee80211_sub_if_data*,int) ; 
 int /*<<< orphan*/  kfree_rcu (struct beacon_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_path_flush_by_iface (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 struct beacon_data* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_head ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sta_info_flush (struct ieee80211_sub_if_data*) ; 

void ieee80211_stop_mesh(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	struct beacon_data *bcn;

	netif_carrier_off(sdata->dev);

	/* flush STAs and mpaths on this iface */
	sta_info_flush(sdata);
	ieee80211_free_keys(sdata, true);
	mesh_path_flush_by_iface(sdata);

	/* stop the beacon */
	ifmsh->mesh_id_len = 0;
	sdata->vif.bss_conf.enable_beacon = false;
	clear_bit(SDATA_STATE_OFFCHANNEL_BEACON_STOPPED, &sdata->state);
	ieee80211_bss_info_change_notify(sdata, BSS_CHANGED_BEACON_ENABLED);

	/* remove beacon */
	bcn = rcu_dereference_protected(ifmsh->beacon,
					lockdep_is_held(&sdata->wdev.mtx));
	RCU_INIT_POINTER(ifmsh->beacon, NULL);
	kfree_rcu(bcn, rcu_head);

	/* free all potentially still buffered group-addressed frames */
	local->total_ps_buffered -= skb_queue_len(&ifmsh->ps.bc_buf);
	skb_queue_purge(&ifmsh->ps.bc_buf);

	del_timer_sync(&sdata->u.mesh.housekeeping_timer);
	del_timer_sync(&sdata->u.mesh.mesh_path_root_timer);
	del_timer_sync(&sdata->u.mesh.mesh_path_timer);

	/* clear any mesh work (for next join) we may have accrued */
	ifmsh->wrkq_flags = 0;
	ifmsh->mbss_changed = 0;

	local->fif_other_bss--;
	atomic_dec(&local->iff_allmultis);
	ieee80211_configure_filter(local);
}