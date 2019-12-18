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
struct dlm_lockstatus {int status; } ;
struct dlm_lock_resource {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dead_node; int /*<<< orphan*/  new_master; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  node_num; TYPE_1__ reco; int /*<<< orphan*/  dlm_reco_thread_wq; int /*<<< orphan*/  spinlock; } ;
typedef  int /*<<< orphan*/  lksb ;
typedef  enum dlm_status { ____Placeholder_dlm_status } dlm_status ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_DENIED ; 
 int DLM_NORMAL ; 
 int DLM_NOTQUEUED ; 
 int DLM_RECOVERING ; 
 int /*<<< orphan*/  DLM_RECOVERY_LOCK_NAME ; 
 int /*<<< orphan*/  DLM_RECOVERY_LOCK_NAME_LEN ; 
 int EEXIST ; 
 int EINVAL ; 
 int /*<<< orphan*/  LKM_CANCEL ; 
 int /*<<< orphan*/  LKM_EXMODE ; 
 int LKM_NOQUEUE ; 
 int LKM_RECOVERY ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  O2NM_INVALID_NODE_NUM ; 
 int /*<<< orphan*/  dlm_errname (int) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 struct dlm_lock_resource* dlm_lookup_lockres (struct dlm_ctxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_reco_ast ; 
 int /*<<< orphan*/  dlm_reco_bast ; 
 scalar_t__ dlm_reco_master_ready (struct dlm_ctxt*) ; 
 int /*<<< orphan*/  dlm_reco_unlock_ast ; 
 int dlm_send_begin_reco_message (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_set_reco_master (struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int dlmlock (struct dlm_ctxt*,int /*<<< orphan*/ ,struct dlm_lockstatus*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_ctxt*,int /*<<< orphan*/ ) ; 
 int dlmunlock (struct dlm_ctxt*,struct dlm_lockstatus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_ctxt*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct dlm_lockstatus*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event_timeout (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dlm_pick_recovery_master(struct dlm_ctxt *dlm)
{
	enum dlm_status ret;
	struct dlm_lockstatus lksb;
	int status = -EINVAL;

	mlog(0, "starting recovery of %s at %lu, dead=%u, this=%u\n",
	     dlm->name, jiffies, dlm->reco.dead_node, dlm->node_num);
again:
	memset(&lksb, 0, sizeof(lksb));

	ret = dlmlock(dlm, LKM_EXMODE, &lksb, LKM_NOQUEUE|LKM_RECOVERY,
		      DLM_RECOVERY_LOCK_NAME, DLM_RECOVERY_LOCK_NAME_LEN,
		      dlm_reco_ast, dlm, dlm_reco_bast);

	mlog(0, "%s: dlmlock($RECOVERY) returned %d, lksb=%d\n",
	     dlm->name, ret, lksb.status);

	if (ret == DLM_NORMAL) {
		mlog(0, "dlm=%s dlmlock says I got it (this=%u)\n",
		     dlm->name, dlm->node_num);

		/* got the EX lock.  check to see if another node
		 * just became the reco master */
		if (dlm_reco_master_ready(dlm)) {
			mlog(0, "%s: got reco EX lock, but %u will "
			     "do the recovery\n", dlm->name,
			     dlm->reco.new_master);
			status = -EEXIST;
		} else {
			status = 0;

			/* see if recovery was already finished elsewhere */
			spin_lock(&dlm->spinlock);
			if (dlm->reco.dead_node == O2NM_INVALID_NODE_NUM) {
				status = -EINVAL;
				mlog(0, "%s: got reco EX lock, but "
				     "node got recovered already\n", dlm->name);
				if (dlm->reco.new_master != O2NM_INVALID_NODE_NUM) {
					mlog(ML_ERROR, "%s: new master is %u "
					     "but no dead node!\n",
					     dlm->name, dlm->reco.new_master);
					BUG();
				}
			}
			spin_unlock(&dlm->spinlock);
		}

		/* if this node has actually become the recovery master,
		 * set the master and send the messages to begin recovery */
		if (!status) {
			mlog(0, "%s: dead=%u, this=%u, sending "
			     "begin_reco now\n", dlm->name,
			     dlm->reco.dead_node, dlm->node_num);
			status = dlm_send_begin_reco_message(dlm,
				      dlm->reco.dead_node);
			/* this always succeeds */
			BUG_ON(status);

			/* set the new_master to this node */
			spin_lock(&dlm->spinlock);
			dlm_set_reco_master(dlm, dlm->node_num);
			spin_unlock(&dlm->spinlock);
		}

		/* recovery lock is a special case.  ast will not get fired,
		 * so just go ahead and unlock it. */
		ret = dlmunlock(dlm, &lksb, 0, dlm_reco_unlock_ast, dlm);
		if (ret == DLM_DENIED) {
			mlog(0, "got DLM_DENIED, trying LKM_CANCEL\n");
			ret = dlmunlock(dlm, &lksb, LKM_CANCEL, dlm_reco_unlock_ast, dlm);
		}
		if (ret != DLM_NORMAL) {
			/* this would really suck. this could only happen
			 * if there was a network error during the unlock
			 * because of node death.  this means the unlock
			 * is actually "done" and the lock structure is
			 * even freed.  we can continue, but only
			 * because this specific lock name is special. */
			mlog(ML_ERROR, "dlmunlock returned %d\n", ret);
		}
	} else if (ret == DLM_NOTQUEUED) {
		mlog(0, "dlm=%s dlmlock says another node got it (this=%u)\n",
		     dlm->name, dlm->node_num);
		/* another node is master. wait on
		 * reco.new_master != O2NM_INVALID_NODE_NUM
		 * for at most one second */
		wait_event_timeout(dlm->dlm_reco_thread_wq,
					 dlm_reco_master_ready(dlm),
					 msecs_to_jiffies(1000));
		if (!dlm_reco_master_ready(dlm)) {
			mlog(0, "%s: reco master taking awhile\n",
			     dlm->name);
			goto again;
		}
		/* another node has informed this one that it is reco master */
		mlog(0, "%s: reco master %u is ready to recover %u\n",
		     dlm->name, dlm->reco.new_master, dlm->reco.dead_node);
		status = -EEXIST;
	} else if (ret == DLM_RECOVERING) {
		mlog(0, "dlm=%s dlmlock says master node died (this=%u)\n",
		     dlm->name, dlm->node_num);
		goto again;
	} else {
		struct dlm_lock_resource *res;

		/* dlmlock returned something other than NOTQUEUED or NORMAL */
		mlog(ML_ERROR, "%s: got %s from dlmlock($RECOVERY), "
		     "lksb.status=%s\n", dlm->name, dlm_errname(ret),
		     dlm_errname(lksb.status));
		res = dlm_lookup_lockres(dlm, DLM_RECOVERY_LOCK_NAME,
					 DLM_RECOVERY_LOCK_NAME_LEN);
		if (res) {
			dlm_print_one_lock_resource(res);
			dlm_lockres_put(res);
		} else {
			mlog(ML_ERROR, "recovery lock not found\n");
		}
		BUG();
	}

	return status;
}