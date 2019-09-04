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
struct mesh_table {int /*<<< orphan*/  entries; } ;
struct mesh_path {int flags; int /*<<< orphan*/  timer; int /*<<< orphan*/  state_lock; struct ieee80211_sub_if_data* sdata; } ;
struct TYPE_3__ {int /*<<< orphan*/  mpaths; } ;
struct TYPE_4__ {TYPE_1__ mesh; } ;
struct ieee80211_sub_if_data {TYPE_2__ u; } ;

/* Variables and functions */
 int MESH_PATH_DELETED ; 
 int MESH_PATH_RESOLVING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct mesh_path*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mesh_gate_del (struct mesh_table*,struct mesh_path*) ; 
 int /*<<< orphan*/  rcu ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mesh_path_free_rcu(struct mesh_table *tbl,
			       struct mesh_path *mpath)
{
	struct ieee80211_sub_if_data *sdata = mpath->sdata;

	spin_lock_bh(&mpath->state_lock);
	mpath->flags |= MESH_PATH_RESOLVING | MESH_PATH_DELETED;
	mesh_gate_del(tbl, mpath);
	spin_unlock_bh(&mpath->state_lock);
	del_timer_sync(&mpath->timer);
	atomic_dec(&sdata->u.mesh.mpaths);
	atomic_dec(&tbl->entries);
	kfree_rcu(mpath, rcu);
}