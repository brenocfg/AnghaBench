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
struct subprocess_info {int wait; int retval; int /*<<< orphan*/ * complete; int /*<<< orphan*/  work; int /*<<< orphan*/  path; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int EBUSY ; 
 int EINVAL ; 
 int UMH_KILLABLE ; 
 int UMH_NO_WAIT ; 
 int /*<<< orphan*/  call_usermodehelper_freeinfo (struct subprocess_info*) ; 
 int /*<<< orphan*/  done ; 
 int /*<<< orphan*/  helper_lock () ; 
 int /*<<< orphan*/  helper_unlock () ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  system_unbound_wq ; 
 scalar_t__ usermodehelper_disabled ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 
 int wait_for_completion_killable (int /*<<< orphan*/ *) ; 
 scalar_t__ xchg (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int call_usermodehelper_exec(struct subprocess_info *sub_info, int wait)
{
	DECLARE_COMPLETION_ONSTACK(done);
	int retval = 0;

	if (!sub_info->path) {
		call_usermodehelper_freeinfo(sub_info);
		return -EINVAL;
	}
	helper_lock();
	if (usermodehelper_disabled) {
		retval = -EBUSY;
		goto out;
	}

	/*
	 * If there is no binary for us to call, then just return and get out of
	 * here.  This allows us to set STATIC_USERMODEHELPER_PATH to "" and
	 * disable all call_usermodehelper() calls.
	 */
	if (strlen(sub_info->path) == 0)
		goto out;

	/*
	 * Set the completion pointer only if there is a waiter.
	 * This makes it possible to use umh_complete to free
	 * the data structure in case of UMH_NO_WAIT.
	 */
	sub_info->complete = (wait == UMH_NO_WAIT) ? NULL : &done;
	sub_info->wait = wait;

	queue_work(system_unbound_wq, &sub_info->work);
	if (wait == UMH_NO_WAIT)	/* task has freed sub_info */
		goto unlock;

	if (wait & UMH_KILLABLE) {
		retval = wait_for_completion_killable(&done);
		if (!retval)
			goto wait_done;

		/* umh_complete() will see NULL and free sub_info */
		if (xchg(&sub_info->complete, NULL))
			goto unlock;
		/* fallthrough, umh_complete() was already called */
	}

	wait_for_completion(&done);
wait_done:
	retval = sub_info->retval;
out:
	call_usermodehelper_freeinfo(sub_info);
unlock:
	helper_unlock();
	return retval;
}