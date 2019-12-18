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
typedef  int /*<<< orphan*/  wait_queue_head_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int EINTR ; 
 int /*<<< orphan*/  NLMCLNT_GRACE_WAIT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  finish_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_timeout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signalled () ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static int nlm_wait_on_grace(wait_queue_head_t *queue)
{
	DEFINE_WAIT(wait);
	int status = -EINTR;

	prepare_to_wait(queue, &wait, TASK_INTERRUPTIBLE);
	if (!signalled ()) {
		schedule_timeout(NLMCLNT_GRACE_WAIT);
		try_to_freeze();
		if (!signalled ())
			status = 0;
	}
	finish_wait(queue, &wait);
	return status;
}