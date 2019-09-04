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
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 scalar_t__ simple_thread_cnt ; 
 int /*<<< orphan*/ * simple_tsk_fn ; 
 int /*<<< orphan*/  thread_mutex ; 

void foo_bar_unreg(void)
{
	mutex_lock(&thread_mutex);
	if (--simple_thread_cnt)
		goto out;

	pr_info("Killing thread for foo_bar_fn\n");
	if (simple_tsk_fn)
		kthread_stop(simple_tsk_fn);
	simple_tsk_fn = NULL;
 out:
	mutex_unlock(&thread_mutex);
}