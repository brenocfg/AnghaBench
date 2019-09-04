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
typedef  char* u8 ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int migration_pending; int state; int /*<<< orphan*/  spinlock; TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; int /*<<< orphan*/  migration_wq; int /*<<< orphan*/  ast_wq; int /*<<< orphan*/  node_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_LOCK_RES_BLOCK_DIRTY ; 
 int DLM_LOCK_RES_DIRTY ; 
 int DLM_LOCK_RES_MIGRATING ; 
 int EHOSTDOWN ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  __dlm_lockres_reserve_ast (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_kick_thread (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_is_dirty (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_release_ast (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_migration_can_proceed (struct dlm_ctxt*,struct dlm_lock_resource*,char*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int wait_event_interruptible_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_mark_lockres_migrating(struct dlm_ctxt *dlm,
				       struct dlm_lock_resource *res,
				       u8 target)
{
	int ret = 0;

	mlog(0, "dlm_mark_lockres_migrating: %.*s, from %u to %u\n",
	       res->lockname.len, res->lockname.name, dlm->node_num,
	       target);
	/* need to set MIGRATING flag on lockres.  this is done by
	 * ensuring that all asts have been flushed for this lockres. */
	spin_lock(&res->spinlock);
	BUG_ON(res->migration_pending);
	res->migration_pending = 1;
	/* strategy is to reserve an extra ast then release
	 * it below, letting the release do all of the work */
	__dlm_lockres_reserve_ast(res);
	spin_unlock(&res->spinlock);

	/* now flush all the pending asts */
	dlm_kick_thread(dlm, res);
	/* before waiting on DIRTY, block processes which may
	 * try to dirty the lockres before MIGRATING is set */
	spin_lock(&res->spinlock);
	BUG_ON(res->state & DLM_LOCK_RES_BLOCK_DIRTY);
	res->state |= DLM_LOCK_RES_BLOCK_DIRTY;
	spin_unlock(&res->spinlock);
	/* now wait on any pending asts and the DIRTY state */
	wait_event(dlm->ast_wq, !dlm_lockres_is_dirty(dlm, res));
	dlm_lockres_release_ast(dlm, res);

	mlog(0, "about to wait on migration_wq, dirty=%s\n",
	       res->state & DLM_LOCK_RES_DIRTY ? "yes" : "no");
	/* if the extra ref we just put was the final one, this
	 * will pass thru immediately.  otherwise, we need to wait
	 * for the last ast to finish. */
again:
	ret = wait_event_interruptible_timeout(dlm->migration_wq,
		   dlm_migration_can_proceed(dlm, res, target),
		   msecs_to_jiffies(1000));
	if (ret < 0) {
		mlog(0, "woken again: migrating? %s, dead? %s\n",
		       res->state & DLM_LOCK_RES_MIGRATING ? "yes":"no",
		       test_bit(target, dlm->domain_map) ? "no":"yes");
	} else {
		mlog(0, "all is well: migrating? %s, dead? %s\n",
		       res->state & DLM_LOCK_RES_MIGRATING ? "yes":"no",
		       test_bit(target, dlm->domain_map) ? "no":"yes");
	}
	if (!dlm_migration_can_proceed(dlm, res, target)) {
		mlog(0, "trying again...\n");
		goto again;
	}

	ret = 0;
	/* did the target go down or die? */
	spin_lock(&dlm->spinlock);
	if (!test_bit(target, dlm->domain_map)) {
		mlog(ML_ERROR, "aha. migration target %u just went down\n",
		     target);
		ret = -EHOSTDOWN;
	}
	spin_unlock(&dlm->spinlock);

	/*
	 * if target is down, we need to clear DLM_LOCK_RES_BLOCK_DIRTY for
	 * another try; otherwise, we are sure the MIGRATING state is there,
	 * drop the unneeded state which blocked threads trying to DIRTY
	 */
	spin_lock(&res->spinlock);
	BUG_ON(!(res->state & DLM_LOCK_RES_BLOCK_DIRTY));
	res->state &= ~DLM_LOCK_RES_BLOCK_DIRTY;
	if (!ret)
		BUG_ON(!(res->state & DLM_LOCK_RES_MIGRATING));
	else
		res->migration_pending = 0;
	spin_unlock(&res->spinlock);

	/*
	 * at this point:
	 *
	 *   o the DLM_LOCK_RES_MIGRATING flag is set if target not down
	 *   o there are no pending asts on this lockres
	 *   o all processes trying to reserve an ast on this
	 *     lockres must wait for the MIGRATING flag to clear
	 */
	return ret;
}