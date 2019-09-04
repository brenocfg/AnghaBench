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
typedef  unsigned long long u64 ;
struct TYPE_6__ {int beacon_int; } ;
struct TYPE_7__ {TYPE_2__ bss_conf; } ;
struct ieee80211_if_mesh {unsigned long long sync_offset_clockdrift_max; int /*<<< orphan*/  sync_offset_lock; } ;
struct TYPE_5__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {TYPE_3__ vif; TYPE_1__ u; struct ieee80211_local* local; } ;
struct ieee80211_local {TYPE_4__* ops; } ;
struct TYPE_8__ {scalar_t__ offset_tsf; } ;

/* Variables and functions */
 unsigned long long drv_get_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  drv_offset_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*,unsigned long long) ; 
 int /*<<< orphan*/  drv_set_tsf (struct ieee80211_local*,struct ieee80211_sub_if_data*,unsigned long long) ; 
 int /*<<< orphan*/  msync_dbg (struct ieee80211_sub_if_data*,char*,long long,...) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mesh_sync_adjust_tsf(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_local *local = sdata->local;
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;
	/* sdata->vif.bss_conf.beacon_int in 1024us units, 0.04% */
	u64 beacon_int_fraction = sdata->vif.bss_conf.beacon_int * 1024 / 2500;
	u64 tsf;
	u64 tsfdelta;

	spin_lock_bh(&ifmsh->sync_offset_lock);
	if (ifmsh->sync_offset_clockdrift_max < beacon_int_fraction) {
		msync_dbg(sdata, "TSF : max clockdrift=%lld; adjusting\n",
			  (long long) ifmsh->sync_offset_clockdrift_max);
		tsfdelta = -ifmsh->sync_offset_clockdrift_max;
		ifmsh->sync_offset_clockdrift_max = 0;
	} else {
		msync_dbg(sdata, "TSF : max clockdrift=%lld; adjusting by %llu\n",
			  (long long) ifmsh->sync_offset_clockdrift_max,
			  (unsigned long long) beacon_int_fraction);
		tsfdelta = -beacon_int_fraction;
		ifmsh->sync_offset_clockdrift_max -= beacon_int_fraction;
	}
	spin_unlock_bh(&ifmsh->sync_offset_lock);

	if (local->ops->offset_tsf) {
		drv_offset_tsf(local, sdata, tsfdelta);
	} else {
		tsf = drv_get_tsf(local, sdata);
		if (tsf != -1ULL)
			drv_set_tsf(local, sdata, tsf + tsfdelta);
	}
}