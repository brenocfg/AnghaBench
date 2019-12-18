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
struct timer_list {int dummy; } ;
struct mesh_path {int flags; scalar_t__ discovery_retries; int discovery_timeout; int /*<<< orphan*/  is_gate; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  exp_time; struct ieee80211_sub_if_data* sdata; } ;
struct ieee80211_sub_if_data {TYPE_1__* local; } ;
struct TYPE_2__ {scalar_t__ quiescing; } ;

/* Variables and functions */
 int MESH_PATH_REQ_QUEUED ; 
 int MESH_PATH_RESOLVED ; 
 int MESH_PATH_RESOLVING ; 
 struct mesh_path* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ max_preq_retries (struct ieee80211_sub_if_data*) ; 
 scalar_t__ mesh_gate_num (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mesh_path_flush_pending (struct mesh_path*) ; 
 int mesh_path_send_to_gates (struct mesh_path*) ; 
 int /*<<< orphan*/  mesh_queue_preq (struct mesh_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mhwmp_dbg (struct ieee80211_sub_if_data*,char*) ; 
 struct mesh_path* mpath ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer ; 

void mesh_path_timer(struct timer_list *t)
{
	struct mesh_path *mpath = from_timer(mpath, t, timer);
	struct ieee80211_sub_if_data *sdata = mpath->sdata;
	int ret;

	if (sdata->local->quiescing)
		return;

	spin_lock_bh(&mpath->state_lock);
	if (mpath->flags & MESH_PATH_RESOLVED ||
			(!(mpath->flags & MESH_PATH_RESOLVING))) {
		mpath->flags &= ~(MESH_PATH_RESOLVING | MESH_PATH_RESOLVED);
		spin_unlock_bh(&mpath->state_lock);
	} else if (mpath->discovery_retries < max_preq_retries(sdata)) {
		++mpath->discovery_retries;
		mpath->discovery_timeout *= 2;
		mpath->flags &= ~MESH_PATH_REQ_QUEUED;
		spin_unlock_bh(&mpath->state_lock);
		mesh_queue_preq(mpath, 0);
	} else {
		mpath->flags &= ~(MESH_PATH_RESOLVING |
				  MESH_PATH_RESOLVED |
				  MESH_PATH_REQ_QUEUED);
		mpath->exp_time = jiffies;
		spin_unlock_bh(&mpath->state_lock);
		if (!mpath->is_gate && mesh_gate_num(sdata) > 0) {
			ret = mesh_path_send_to_gates(mpath);
			if (ret)
				mhwmp_dbg(sdata, "no gate was reachable\n");
		} else
			mesh_path_flush_pending(mpath);
	}
}