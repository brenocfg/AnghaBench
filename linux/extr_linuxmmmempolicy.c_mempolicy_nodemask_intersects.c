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
struct task_struct {struct mempolicy* mempolicy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nodes; } ;
struct mempolicy {int mode; TYPE_1__ v; } ;
typedef  int /*<<< orphan*/  nodemask_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  MPOL_BIND 130 
#define  MPOL_INTERLEAVE 129 
#define  MPOL_PREFERRED 128 
 int nodes_intersects (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  task_lock (struct task_struct*) ; 
 int /*<<< orphan*/  task_unlock (struct task_struct*) ; 

bool mempolicy_nodemask_intersects(struct task_struct *tsk,
					const nodemask_t *mask)
{
	struct mempolicy *mempolicy;
	bool ret = true;

	if (!mask)
		return ret;
	task_lock(tsk);
	mempolicy = tsk->mempolicy;
	if (!mempolicy)
		goto out;

	switch (mempolicy->mode) {
	case MPOL_PREFERRED:
		/*
		 * MPOL_PREFERRED and MPOL_F_LOCAL are only preferred nodes to
		 * allocate from, they may fallback to other nodes when oom.
		 * Thus, it's possible for tsk to have allocated memory from
		 * nodes in mask.
		 */
		break;
	case MPOL_BIND:
	case MPOL_INTERLEAVE:
		ret = nodes_intersects(mempolicy->v.nodes, *mask);
		break;
	default:
		BUG();
	}
out:
	task_unlock(tsk);
	return ret;
}