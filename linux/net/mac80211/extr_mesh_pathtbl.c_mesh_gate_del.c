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
struct mesh_table {int /*<<< orphan*/  gates_lock; } ;
struct mesh_path {int is_gate; TYPE_3__* sdata; int /*<<< orphan*/  dst; int /*<<< orphan*/  gate_list; int /*<<< orphan*/  state_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  num_gates; } ;
struct TYPE_5__ {TYPE_1__ mesh; } ;
struct TYPE_6__ {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpath_dbg (TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mesh_gate_del(struct mesh_table *tbl, struct mesh_path *mpath)
{
	lockdep_assert_held(&mpath->state_lock);
	if (!mpath->is_gate)
		return;

	mpath->is_gate = false;
	spin_lock_bh(&tbl->gates_lock);
	hlist_del_rcu(&mpath->gate_list);
	mpath->sdata->u.mesh.num_gates--;
	spin_unlock_bh(&tbl->gates_lock);

	mpath_dbg(mpath->sdata,
		  "Mesh path: Deleted gate: %pM. %d known gates\n",
		  mpath->dst, mpath->sdata->u.mesh.num_gates);
}