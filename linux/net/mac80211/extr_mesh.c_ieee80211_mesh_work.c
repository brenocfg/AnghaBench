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
struct TYPE_3__ {int /*<<< orphan*/  dot11MeshHWMPpreqMinInterval; } ;
struct ieee80211_if_mesh {int /*<<< orphan*/  wrkq_flags; TYPE_1__ mshcfg; scalar_t__ last_preq; scalar_t__ preq_queue_len; int /*<<< orphan*/  mesh_id_len; } ;
struct TYPE_4__ {struct ieee80211_if_mesh mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  MESH_WORK_DRIFT_ADJUST ; 
 int /*<<< orphan*/  MESH_WORK_HOUSEKEEPING ; 
 int /*<<< orphan*/  MESH_WORK_MBSS_CHANGED ; 
 int /*<<< orphan*/  MESH_WORK_ROOT ; 
 int /*<<< orphan*/  ieee80211_mesh_housekeeping (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  ieee80211_mesh_rootpath (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mesh_bss_info_changed (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mesh_path_start_discovery (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mesh_sync_adjust_tsf (struct ieee80211_sub_if_data*) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdata_lock (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  sdata_unlock (struct ieee80211_sub_if_data*) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 

void ieee80211_mesh_work(struct ieee80211_sub_if_data *sdata)
{
	struct ieee80211_if_mesh *ifmsh = &sdata->u.mesh;

	sdata_lock(sdata);

	/* mesh already went down */
	if (!sdata->u.mesh.mesh_id_len)
		goto out;

	if (ifmsh->preq_queue_len &&
	    time_after(jiffies,
		       ifmsh->last_preq + msecs_to_jiffies(ifmsh->mshcfg.dot11MeshHWMPpreqMinInterval)))
		mesh_path_start_discovery(sdata);

	if (test_and_clear_bit(MESH_WORK_HOUSEKEEPING, &ifmsh->wrkq_flags))
		ieee80211_mesh_housekeeping(sdata);

	if (test_and_clear_bit(MESH_WORK_ROOT, &ifmsh->wrkq_flags))
		ieee80211_mesh_rootpath(sdata);

	if (test_and_clear_bit(MESH_WORK_DRIFT_ADJUST, &ifmsh->wrkq_flags))
		mesh_sync_adjust_tsf(sdata);

	if (test_and_clear_bit(MESH_WORK_MBSS_CHANGED, &ifmsh->wrkq_flags))
		mesh_bss_info_changed(sdata);
out:
	sdata_unlock(sdata);
}