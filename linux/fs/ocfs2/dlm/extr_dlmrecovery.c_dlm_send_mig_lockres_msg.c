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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct dlm_migratable_lockres {int flags; int master; scalar_t__ num_locks; int /*<<< orphan*/  lockname; int /*<<< orphan*/  lockname_len; int /*<<< orphan*/  total_locks; int /*<<< orphan*/  mig_cookie; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  name; } ;
struct dlm_lock_resource {TYPE_1__ lockname; } ;
struct dlm_ctxt {int /*<<< orphan*/  name; int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ DLM_MAX_MIGRATABLE_LOCKS ; 
 int /*<<< orphan*/  DLM_MIG_LOCKRES_MSG ; 
 int DLM_MRES_ALL_DONE ; 
 int DLM_MRES_MIGRATION ; 
 int EFAULT ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_init_migratable_lockres (struct dlm_migratable_lockres*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ml ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int o2net_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct dlm_migratable_lockres*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  struct_size (struct dlm_migratable_lockres*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int dlm_send_mig_lockres_msg(struct dlm_ctxt *dlm,
				      struct dlm_migratable_lockres *mres,
				      u8 send_to,
				      struct dlm_lock_resource *res,
				      int total_locks)
{
	u64 mig_cookie = be64_to_cpu(mres->mig_cookie);
	int mres_total_locks = be32_to_cpu(mres->total_locks);
	int ret = 0, status = 0;
	u8 orig_flags = mres->flags,
	   orig_master = mres->master;

	BUG_ON(mres->num_locks > DLM_MAX_MIGRATABLE_LOCKS);
	if (!mres->num_locks)
		return 0;

	/* add an all-done flag if we reached the last lock */
	orig_flags = mres->flags;
	BUG_ON(total_locks > mres_total_locks);
	if (total_locks == mres_total_locks)
		mres->flags |= DLM_MRES_ALL_DONE;

	mlog(0, "%s:%.*s: sending mig lockres (%s) to %u\n",
	     dlm->name, res->lockname.len, res->lockname.name,
	     orig_flags & DLM_MRES_MIGRATION ? "migration" : "recovery",
	     send_to);

	/* send it */
	ret = o2net_send_message(DLM_MIG_LOCKRES_MSG, dlm->key, mres,
				 struct_size(mres, ml, mres->num_locks),
				 send_to, &status);
	if (ret < 0) {
		/* XXX: negative status is not handled.
		 * this will end up killing this node. */
		mlog(ML_ERROR, "%s: res %.*s, Error %d send MIG_LOCKRES to "
		     "node %u (%s)\n", dlm->name, mres->lockname_len,
		     mres->lockname, ret, send_to,
		     (orig_flags & DLM_MRES_MIGRATION ?
		      "migration" : "recovery"));
	} else {
		/* might get an -ENOMEM back here */
		ret = status;
		if (ret < 0) {
			mlog_errno(ret);

			if (ret == -EFAULT) {
				mlog(ML_ERROR, "node %u told me to kill "
				     "myself!\n", send_to);
				BUG();
			}
		}
	}

	/* zero and reinit the message buffer */
	dlm_init_migratable_lockres(mres, res->lockname.name,
				    res->lockname.len, mres_total_locks,
				    mig_cookie, orig_flags, orig_master);
	return ret;
}