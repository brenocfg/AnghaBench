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

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 long EINVAL ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  umhelper_sem ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usermodehelper_disabled ; 
 int /*<<< orphan*/  usermodehelper_disabled_waitq ; 
 int /*<<< orphan*/  wait ; 

long usermodehelper_read_lock_wait(long timeout)
{
	DEFINE_WAIT(wait);

	if (timeout < 0)
		return -EINVAL;

	down_read(&umhelper_sem);
	for (;;) {
		prepare_to_wait(&usermodehelper_disabled_waitq, &wait,
				TASK_UNINTERRUPTIBLE);
		if (!usermodehelper_disabled)
			break;

		up_read(&umhelper_sem);

		timeout = schedule_timeout(timeout);
		if (!timeout)
			break;

		down_read(&umhelper_sem);
	}
	finish_wait(&usermodehelper_disabled_waitq, &wait);
	return timeout;
}