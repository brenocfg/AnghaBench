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
typedef  int /*<<< orphan*/  u8 ;
struct dlm_node_iter {int /*<<< orphan*/  node_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  state; TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  node_num; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  domain_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  DLM_ASSERT_MASTER_FINISH_MIGRATION ; 
 int /*<<< orphan*/  DLM_LOCK_RES_MIGRATING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlm_do_assert_master (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlm_do_migrate_request (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_node_iter*) ; 
 int /*<<< orphan*/  dlm_kick_thread (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_lockres_set_refmap_bit (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_node_iter_init (int /*<<< orphan*/ ,struct dlm_node_iter*) ; 
 int /*<<< orphan*/  dlm_set_lockres_owner (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

int dlm_finish_migration(struct dlm_ctxt *dlm, struct dlm_lock_resource *res,
			 u8 old_master)
{
	struct dlm_node_iter iter;
	int ret = 0;

	spin_lock(&dlm->spinlock);
	dlm_node_iter_init(dlm->domain_map, &iter);
	clear_bit(old_master, iter.node_map);
	clear_bit(dlm->node_num, iter.node_map);
	spin_unlock(&dlm->spinlock);

	/* ownership of the lockres is changing.  account for the
	 * mastery reference here since old_master will briefly have
	 * a reference after the migration completes */
	spin_lock(&res->spinlock);
	dlm_lockres_set_refmap_bit(dlm, res, old_master);
	spin_unlock(&res->spinlock);

	mlog(0, "now time to do a migrate request to other nodes\n");
	ret = dlm_do_migrate_request(dlm, res, old_master,
				     dlm->node_num, &iter);
	if (ret < 0) {
		mlog_errno(ret);
		goto leave;
	}

	mlog(0, "doing assert master of %.*s to all except the original node\n",
	     res->lockname.len, res->lockname.name);
	/* this call now finishes out the nodemap
	 * even if one or more nodes die */
	ret = dlm_do_assert_master(dlm, res, iter.node_map,
				   DLM_ASSERT_MASTER_FINISH_MIGRATION);
	if (ret < 0) {
		/* no longer need to retry.  all living nodes contacted. */
		mlog_errno(ret);
		ret = 0;
	}

	memset(iter.node_map, 0, sizeof(iter.node_map));
	set_bit(old_master, iter.node_map);
	mlog(0, "doing assert master of %.*s back to %u\n",
	     res->lockname.len, res->lockname.name, old_master);
	ret = dlm_do_assert_master(dlm, res, iter.node_map,
				   DLM_ASSERT_MASTER_FINISH_MIGRATION);
	if (ret < 0) {
		mlog(0, "assert master to original master failed "
		     "with %d.\n", ret);
		/* the only nonzero status here would be because of
		 * a dead original node.  we're done. */
		ret = 0;
	}

	/* all done, set the owner, clear the flag */
	spin_lock(&res->spinlock);
	dlm_set_lockres_owner(dlm, res, dlm->node_num);
	res->state &= ~DLM_LOCK_RES_MIGRATING;
	spin_unlock(&res->spinlock);
	/* re-dirty it on the new master */
	dlm_kick_thread(dlm, res);
	wake_up(&res->wq);
leave:
	return ret;
}