#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct dlm_rsb {int dummy; } ;
struct dlm_lkb {int lkb_exflags; } ;

/* Variables and functions */
 int DLM_LKF_NODLCKWT ; 
 int /*<<< orphan*/  DLM_LKSTS_CONVERT ; 
 int /*<<< orphan*/  DLM_LOCK_IV ; 
 int EAGAIN ; 
 int EDEADLK ; 
 int EINPROGRESS ; 
 scalar_t__ _can_be_granted (struct dlm_rsb*,struct dlm_lkb*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_lkb (struct dlm_rsb*,struct dlm_lkb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_timeout (struct dlm_lkb*) ; 
 scalar_t__ can_be_granted (struct dlm_rsb*,struct dlm_lkb*,int,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ can_be_queued (struct dlm_lkb*) ; 
 int /*<<< orphan*/  del_lkb (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  grant_lock (struct dlm_rsb*,struct dlm_lkb*) ; 
 int /*<<< orphan*/  grant_pending_convert (struct dlm_rsb*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_demoted (struct dlm_lkb*) ; 
 int /*<<< orphan*/  queue_cast (struct dlm_rsb*,struct dlm_lkb*,int) ; 
 int /*<<< orphan*/  revert_lock (struct dlm_rsb*,struct dlm_lkb*) ; 

__attribute__((used)) static int do_convert(struct dlm_rsb *r, struct dlm_lkb *lkb)
{
	int error = 0;
	int deadlk = 0;

	/* changing an existing lock may allow others to be granted */

	if (can_be_granted(r, lkb, 1, 0, &deadlk)) {
		grant_lock(r, lkb);
		queue_cast(r, lkb, 0);
		goto out;
	}

	/* can_be_granted() detected that this lock would block in a conversion
	   deadlock, so we leave it on the granted queue and return EDEADLK in
	   the ast for the convert. */

	if (deadlk && !(lkb->lkb_exflags & DLM_LKF_NODLCKWT)) {
		/* it's left on the granted queue */
		revert_lock(r, lkb);
		queue_cast(r, lkb, -EDEADLK);
		error = -EDEADLK;
		goto out;
	}

	/* is_demoted() means the can_be_granted() above set the grmode
	   to NL, and left us on the granted queue.  This auto-demotion
	   (due to CONVDEADLK) might mean other locks, and/or this lock, are
	   now grantable.  We have to try to grant other converting locks
	   before we try again to grant this one. */

	if (is_demoted(lkb)) {
		grant_pending_convert(r, DLM_LOCK_IV, NULL, NULL);
		if (_can_be_granted(r, lkb, 1, 0)) {
			grant_lock(r, lkb);
			queue_cast(r, lkb, 0);
			goto out;
		}
		/* else fall through and move to convert queue */
	}

	if (can_be_queued(lkb)) {
		error = -EINPROGRESS;
		del_lkb(r, lkb);
		add_lkb(r, lkb, DLM_LKSTS_CONVERT);
		add_timeout(lkb);
		goto out;
	}

	error = -EAGAIN;
	queue_cast(r, lkb, -EAGAIN);
 out:
	return error;
}