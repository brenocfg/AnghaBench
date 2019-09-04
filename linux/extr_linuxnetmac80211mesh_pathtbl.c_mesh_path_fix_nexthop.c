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
struct sta_info {TYPE_1__* mesh; } ;
struct mesh_path {int sn; int flags; int /*<<< orphan*/  state_lock; scalar_t__ exp_time; scalar_t__ hop_count; scalar_t__ metric; } ;
struct TYPE_2__ {int /*<<< orphan*/  fail_avg; } ;

/* Variables and functions */
 int MESH_PATH_FIXED ; 
 int MESH_PATH_SN_VALID ; 
 int /*<<< orphan*/  ewma_mesh_fail_avg_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ewma_mesh_fail_avg_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_path_activate (struct mesh_path*) ; 
 int /*<<< orphan*/  mesh_path_assign_nexthop (struct mesh_path*,struct sta_info*) ; 
 int /*<<< orphan*/  mesh_path_tx_pending (struct mesh_path*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void mesh_path_fix_nexthop(struct mesh_path *mpath, struct sta_info *next_hop)
{
	spin_lock_bh(&mpath->state_lock);
	mesh_path_assign_nexthop(mpath, next_hop);
	mpath->sn = 0xffff;
	mpath->metric = 0;
	mpath->hop_count = 0;
	mpath->exp_time = 0;
	mpath->flags = MESH_PATH_FIXED | MESH_PATH_SN_VALID;
	mesh_path_activate(mpath);
	spin_unlock_bh(&mpath->state_lock);
	ewma_mesh_fail_avg_init(&next_hop->mesh->fail_avg);
	/* init it at a low value - 0 start is tricky */
	ewma_mesh_fail_avg_add(&next_hop->mesh->fail_avg, 1);
	mesh_path_tx_pending(mpath);
}