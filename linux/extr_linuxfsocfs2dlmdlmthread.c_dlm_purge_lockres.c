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
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dlm_lock_resource {scalar_t__ owner; int state; int /*<<< orphan*/  spinlock; int /*<<< orphan*/  wq; TYPE_1__ lockname; int /*<<< orphan*/  tracking; int /*<<< orphan*/  purge; } ;
struct dlm_ctxt {scalar_t__ node_num; int /*<<< orphan*/  track_lock; int /*<<< orphan*/  name; int /*<<< orphan*/  purge_count; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int DLM_DEREF_RESPONSE_INPROG ; 
 int DLM_LOCK_RES_DROPPING_REF ; 
 int /*<<< orphan*/  DLM_LOCK_RES_SETREF_INPROG ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  ML_NOTICE ; 
 int /*<<< orphan*/  __dlm_lockres_unused (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_unhash_lockres (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_wait_on_lockres_flags (struct dlm_lock_resource*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int dlm_drop_lockres_ref (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  dlm_is_host_down (int) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dlm_purge_lockres(struct dlm_ctxt *dlm,
			     struct dlm_lock_resource *res)
{
	int master;
	int ret = 0;

	assert_spin_locked(&dlm->spinlock);
	assert_spin_locked(&res->spinlock);

	master = (res->owner == dlm->node_num);

	mlog(0, "%s: Purging res %.*s, master %d\n", dlm->name,
	     res->lockname.len, res->lockname.name, master);

	if (!master) {
		if (res->state & DLM_LOCK_RES_DROPPING_REF) {
			mlog(ML_NOTICE, "%s: res %.*s already in DLM_LOCK_RES_DROPPING_REF state\n",
				dlm->name, res->lockname.len, res->lockname.name);
			spin_unlock(&res->spinlock);
			return;
		}

		res->state |= DLM_LOCK_RES_DROPPING_REF;
		/* drop spinlock...  retake below */
		spin_unlock(&res->spinlock);
		spin_unlock(&dlm->spinlock);

		spin_lock(&res->spinlock);
		/* This ensures that clear refmap is sent after the set */
		__dlm_wait_on_lockres_flags(res, DLM_LOCK_RES_SETREF_INPROG);
		spin_unlock(&res->spinlock);

		/* clear our bit from the master's refmap, ignore errors */
		ret = dlm_drop_lockres_ref(dlm, res);
		if (ret < 0) {
			if (!dlm_is_host_down(ret))
				BUG();
		}
		spin_lock(&dlm->spinlock);
		spin_lock(&res->spinlock);
	}

	if (!list_empty(&res->purge)) {
		mlog(0, "%s: Removing res %.*s from purgelist, master %d\n",
		     dlm->name, res->lockname.len, res->lockname.name, master);
		list_del_init(&res->purge);
		dlm_lockres_put(res);
		dlm->purge_count--;
	}

	if (!master && ret == DLM_DEREF_RESPONSE_INPROG) {
		mlog(0, "%s: deref %.*s in progress\n",
			dlm->name, res->lockname.len, res->lockname.name);
		spin_unlock(&res->spinlock);
		return;
	}

	if (!__dlm_lockres_unused(res)) {
		mlog(ML_ERROR, "%s: res %.*s in use after deref\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		__dlm_print_one_lock_resource(res);
		BUG();
	}

	__dlm_unhash_lockres(dlm, res);

	spin_lock(&dlm->track_lock);
	if (!list_empty(&res->tracking))
		list_del_init(&res->tracking);
	else {
		mlog(ML_ERROR, "Resource %.*s not on the Tracking list\n",
				res->lockname.len, res->lockname.name);
		__dlm_print_one_lock_resource(res);
	}
	spin_unlock(&dlm->track_lock);

	/* lockres is not in the hash now.  drop the flag and wake up
	 * any processes waiting in dlm_get_lock_resource. */
	if (!master) {
		res->state &= ~DLM_LOCK_RES_DROPPING_REF;
		spin_unlock(&res->spinlock);
		wake_up(&res->wq);
	} else
		spin_unlock(&res->spinlock);
}