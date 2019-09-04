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
struct dlm_lock_resource {int /*<<< orphan*/  state; TYPE_1__ lockname; int /*<<< orphan*/  tracking; int /*<<< orphan*/  purge; int /*<<< orphan*/  spinlock; } ;
struct dlm_ctxt {int /*<<< orphan*/  track_lock; int /*<<< orphan*/  name; int /*<<< orphan*/  purge_count; int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  DLM_LOCK_RES_DROPPING_REF ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  __dlm_lockres_unused (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_print_one_lock_resource (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  __dlm_unhash_lockres (struct dlm_ctxt*,struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlm_lockres_put (struct dlm_lock_resource*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void __dlm_do_purge_lockres(struct dlm_ctxt *dlm,
		struct dlm_lock_resource *res)
{
	assert_spin_locked(&dlm->spinlock);
	assert_spin_locked(&res->spinlock);

	if (!list_empty(&res->purge)) {
		mlog(0, "%s: Removing res %.*s from purgelist\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		list_del_init(&res->purge);
		dlm_lockres_put(res);
		dlm->purge_count--;
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
		mlog(ML_ERROR, "%s: Resource %.*s not on the Tracking list\n",
		     dlm->name, res->lockname.len, res->lockname.name);
		__dlm_print_one_lock_resource(res);
	}
	spin_unlock(&dlm->track_lock);

	/*
	 * lockres is not in the hash now. drop the flag and wake up
	 * any processes waiting in dlm_get_lock_resource.
	 */
	res->state &= ~DLM_LOCK_RES_DROPPING_REF;
}