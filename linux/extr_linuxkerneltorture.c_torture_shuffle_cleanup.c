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
 int /*<<< orphan*/  VERBOSE_TOROUT_STRING (char*) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shuffle_tmp_mask ; 
 int /*<<< orphan*/ * shuffler_task ; 
 int /*<<< orphan*/  torture_shuffle_task_unregister_all () ; 

__attribute__((used)) static void torture_shuffle_cleanup(void)
{
	torture_shuffle_task_unregister_all();
	if (shuffler_task) {
		VERBOSE_TOROUT_STRING("Stopping torture_shuffle task");
		kthread_stop(shuffler_task);
		free_cpumask_var(shuffle_tmp_mask);
	}
	shuffler_task = NULL;
}