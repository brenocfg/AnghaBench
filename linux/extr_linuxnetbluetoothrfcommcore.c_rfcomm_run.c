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
 int /*<<< orphan*/  BDADDR_ANY ; 
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  DEFINE_WAIT_FUNC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rfcomm_add_listener (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rfcomm_kill_listener () ; 
 int /*<<< orphan*/  rfcomm_process_sessions () ; 
 int /*<<< orphan*/  rfcomm_wq ; 
 int /*<<< orphan*/  set_user_nice (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait ; 
 int /*<<< orphan*/  wait_woken (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  woken_wake_function ; 

__attribute__((used)) static int rfcomm_run(void *unused)
{
	DEFINE_WAIT_FUNC(wait, woken_wake_function);
	BT_DBG("");

	set_user_nice(current, -10);

	rfcomm_add_listener(BDADDR_ANY);

	add_wait_queue(&rfcomm_wq, &wait);
	while (!kthread_should_stop()) {

		/* Process stuff */
		rfcomm_process_sessions();

		wait_woken(&wait, TASK_INTERRUPTIBLE, MAX_SCHEDULE_TIMEOUT);
	}
	remove_wait_queue(&rfcomm_wq, &wait);

	rfcomm_kill_listener();

	return 0;
}