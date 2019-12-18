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
typedef  scalar_t__ u8 ;
struct dlm_master_list_entry {scalar_t__ master; scalar_t__ type; int /*<<< orphan*/  vote_map; int /*<<< orphan*/  woken; int /*<<< orphan*/  wq; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  maybe_map; int /*<<< orphan*/  response_map; int /*<<< orphan*/  node_map; } ;
struct TYPE_2__ {scalar_t__ len; scalar_t__ name; } ;
struct dlm_lock_resource {scalar_t__ owner; int /*<<< orphan*/  spinlock; TYPE_1__ lockname; } ;
struct dlm_ctxt {scalar_t__ name; int node_num; } ;

/* Variables and functions */
 scalar_t__ DLM_LOCK_RES_OWNER_UNKNOWN ; 
 int /*<<< orphan*/  DLM_MASTERY_TIMEOUT_MS ; 
 scalar_t__ DLM_MLE_BLOCK ; 
 int /*<<< orphan*/  ML_ERROR ; 
 scalar_t__ O2NM_MAX_NODES ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_change_lockres_owner (struct dlm_ctxt*,struct dlm_lock_resource*,scalar_t__) ; 
 int dlm_do_assert_master (struct dlm_ctxt*,struct dlm_lock_resource*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dlm_do_master_request (struct dlm_lock_resource*,struct dlm_master_list_entry*,int) ; 
 int dlm_restart_lock_mastery (struct dlm_ctxt*,struct dlm_lock_resource*,struct dlm_master_list_entry*,int) ; 
 int find_next_bit (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int dlm_wait_for_lock_mastery(struct dlm_ctxt *dlm,
				     struct dlm_lock_resource *res,
				     struct dlm_master_list_entry *mle,
				     int *blocked)
{
	u8 m;
	int ret, bit;
	int map_changed, voting_done;
	int assert, sleep;

recheck:
	ret = 0;
	assert = 0;

	/* check if another node has already become the owner */
	spin_lock(&res->spinlock);
	if (res->owner != DLM_LOCK_RES_OWNER_UNKNOWN) {
		mlog(0, "%s:%.*s: owner is suddenly %u\n", dlm->name,
		     res->lockname.len, res->lockname.name, res->owner);
		spin_unlock(&res->spinlock);
		/* this will cause the master to re-assert across
		 * the whole cluster, freeing up mles */
		if (res->owner != dlm->node_num) {
			ret = dlm_do_master_request(res, mle, res->owner);
			if (ret < 0) {
				/* give recovery a chance to run */
				mlog(ML_ERROR, "link to %u went down?: %d\n", res->owner, ret);
				msleep(500);
				goto recheck;
			}
		}
		ret = 0;
		goto leave;
	}
	spin_unlock(&res->spinlock);

	spin_lock(&mle->spinlock);
	m = mle->master;
	map_changed = (memcmp(mle->vote_map, mle->node_map,
			      sizeof(mle->vote_map)) != 0);
	voting_done = (memcmp(mle->vote_map, mle->response_map,
			     sizeof(mle->vote_map)) == 0);

	/* restart if we hit any errors */
	if (map_changed) {
		int b;
		mlog(0, "%s: %.*s: node map changed, restarting\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		ret = dlm_restart_lock_mastery(dlm, res, mle, *blocked);
		b = (mle->type == DLM_MLE_BLOCK);
		if ((*blocked && !b) || (!*blocked && b)) {
			mlog(0, "%s:%.*s: status change: old=%d new=%d\n",
			     dlm->name, res->lockname.len, res->lockname.name,
			     *blocked, b);
			*blocked = b;
		}
		spin_unlock(&mle->spinlock);
		if (ret < 0) {
			mlog_errno(ret);
			goto leave;
		}
		mlog(0, "%s:%.*s: restart lock mastery succeeded, "
		     "rechecking now\n", dlm->name, res->lockname.len,
		     res->lockname.name);
		goto recheck;
	} else {
		if (!voting_done) {
			mlog(0, "map not changed and voting not done "
			     "for %s:%.*s\n", dlm->name, res->lockname.len,
			     res->lockname.name);
		}
	}

	if (m != O2NM_MAX_NODES) {
		/* another node has done an assert!
		 * all done! */
		sleep = 0;
	} else {
		sleep = 1;
		/* have all nodes responded? */
		if (voting_done && !*blocked) {
			bit = find_next_bit(mle->maybe_map, O2NM_MAX_NODES, 0);
			if (dlm->node_num <= bit) {
				/* my node number is lowest.
			 	 * now tell other nodes that I am
				 * mastering this. */
				mle->master = dlm->node_num;
				/* ref was grabbed in get_lock_resource
				 * will be dropped in dlmlock_master */
				assert = 1;
				sleep = 0;
			}
			/* if voting is done, but we have not received
			 * an assert master yet, we must sleep */
		}
	}

	spin_unlock(&mle->spinlock);

	/* sleep if we haven't finished voting yet */
	if (sleep) {
		unsigned long timeo = msecs_to_jiffies(DLM_MASTERY_TIMEOUT_MS);
		atomic_set(&mle->woken, 0);
		(void)wait_event_timeout(mle->wq,
					 (atomic_read(&mle->woken) == 1),
					 timeo);
		if (res->owner == O2NM_MAX_NODES) {
			mlog(0, "%s:%.*s: waiting again\n", dlm->name,
			     res->lockname.len, res->lockname.name);
			goto recheck;
		}
		mlog(0, "done waiting, master is %u\n", res->owner);
		ret = 0;
		goto leave;
	}

	ret = 0;   /* done */
	if (assert) {
		m = dlm->node_num;
		mlog(0, "about to master %.*s here, this=%u\n",
		     res->lockname.len, res->lockname.name, m);
		ret = dlm_do_assert_master(dlm, res, mle->vote_map, 0);
		if (ret) {
			/* This is a failure in the network path,
			 * not in the response to the assert_master
			 * (any nonzero response is a BUG on this node).
			 * Most likely a socket just got disconnected
			 * due to node death. */
			mlog_errno(ret);
		}
		/* no longer need to restart lock mastery.
		 * all living nodes have been contacted. */
		ret = 0;
	}

	/* set the lockres owner */
	spin_lock(&res->spinlock);
	/* mastery reference obtained either during
	 * assert_master_handler or in get_lock_resource */
	dlm_change_lockres_owner(dlm, res, m);
	spin_unlock(&res->spinlock);

leave:
	return ret;
}