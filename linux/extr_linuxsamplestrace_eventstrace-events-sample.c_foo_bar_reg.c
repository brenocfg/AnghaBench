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
 int /*<<< orphan*/  kthread_run (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  simple_thread_cnt ; 
 int /*<<< orphan*/  simple_thread_fn ; 
 int /*<<< orphan*/  simple_tsk_fn ; 
 int /*<<< orphan*/  thread_mutex ; 

int foo_bar_reg(void)
{
	mutex_lock(&thread_mutex);
	if (simple_thread_cnt++)
		goto out;

	pr_info("Starting thread for foo_bar_fn\n");
	/*
	 * We shouldn't be able to start a trace when the module is
	 * unloading (there's other locks to prevent that). But
	 * for consistency sake, we still take the thread_mutex.
	 */
	simple_tsk_fn = kthread_run(simple_thread_fn, NULL, "event-sample-fn");
 out:
	mutex_unlock(&thread_mutex);
	return 0;
}