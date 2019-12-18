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
typedef  enum umh_disable_depth { ____Placeholder_umh_disable_depth } umh_disable_depth ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  RUNNING_HELPERS_TIMEOUT ; 
 int /*<<< orphan*/  UMH_ENABLED ; 
 int /*<<< orphan*/  __usermodehelper_set_disable_depth (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  running_helpers ; 
 int /*<<< orphan*/  running_helpers_waitq ; 
 int /*<<< orphan*/  umhelper_sem ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int usermodehelper_disabled ; 
 long wait_event_timeout (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int __usermodehelper_disable(enum umh_disable_depth depth)
{
	long retval;

	if (!depth)
		return -EINVAL;

	down_write(&umhelper_sem);
	usermodehelper_disabled = depth;
	up_write(&umhelper_sem);

	/*
	 * From now on call_usermodehelper_exec() won't start any new
	 * helpers, so it is sufficient if running_helpers turns out to
	 * be zero at one point (it may be increased later, but that
	 * doesn't matter).
	 */
	retval = wait_event_timeout(running_helpers_waitq,
					atomic_read(&running_helpers) == 0,
					RUNNING_HELPERS_TIMEOUT);
	if (retval)
		return 0;

	__usermodehelper_set_disable_depth(UMH_ENABLED);
	return -EAGAIN;
}