#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mesh_table {int /*<<< orphan*/  gates_lock; int /*<<< orphan*/  known_gates; } ;
struct mesh_path {int is_gate; TYPE_3__* sdata; int /*<<< orphan*/  dst; int /*<<< orphan*/  state_lock; int /*<<< orphan*/  gate_list; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_gates; struct mesh_table* mesh_paths; } ;
struct TYPE_5__ {TYPE_1__ mesh; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 int EEXIST ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpath_dbg (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int mesh_path_add_gate(struct mesh_path *mpath)
{
	struct mesh_table *tbl;
	int err;

	rcu_read_lock();
	tbl = mpath->sdata->u.mesh.mesh_paths;

	spin_lock_bh(&mpath->state_lock);
	if (mpath->is_gate) {
		err = -EEXIST;
		spin_unlock_bh(&mpath->state_lock);
		goto err_rcu;
	}
	mpath->is_gate = true;
	mpath->sdata->u.mesh.num_gates++;

	spin_lock(&tbl->gates_lock);
	hlist_add_head_rcu(&mpath->gate_list, &tbl->known_gates);
	spin_unlock(&tbl->gates_lock);

	spin_unlock_bh(&mpath->state_lock);

	mpath_dbg(mpath->sdata,
		  "Mesh path: Recorded new gate: %pM. %d known gates\n",
		  mpath->dst, mpath->sdata->u.mesh.num_gates);
	err = 0;
err_rcu:
	rcu_read_unlock();
	return err;
}