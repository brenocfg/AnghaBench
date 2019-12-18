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
struct TYPE_2__ {int nrealwriters_stress; int nrealreaders_stress; int /*<<< orphan*/ * lrsa; int /*<<< orphan*/ * lwsa; int /*<<< orphan*/  cur_ops; int /*<<< orphan*/  n_lock_torture_errors; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 TYPE_1__ cxt ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_torture_print_module_parms (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lock_torture_reader ; 
 int /*<<< orphan*/  lock_torture_stats ; 
 int /*<<< orphan*/  lock_torture_stats_print () ; 
 int /*<<< orphan*/  lock_torture_writer ; 
 int /*<<< orphan*/ * reader_tasks ; 
 int /*<<< orphan*/  stats_task ; 
 scalar_t__ torture_cleanup_begin () ; 
 int /*<<< orphan*/  torture_cleanup_end () ; 
 scalar_t__ torture_onoff_failures () ; 
 int /*<<< orphan*/  torture_stop_kthread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * writer_tasks ; 

__attribute__((used)) static void lock_torture_cleanup(void)
{
	int i;

	if (torture_cleanup_begin())
		return;

	/*
	 * Indicates early cleanup, meaning that the test has not run,
	 * such as when passing bogus args when loading the module. As
	 * such, only perform the underlying torture-specific cleanups,
	 * and avoid anything related to locktorture.
	 */
	if (!cxt.lwsa && !cxt.lrsa)
		goto end;

	if (writer_tasks) {
		for (i = 0; i < cxt.nrealwriters_stress; i++)
			torture_stop_kthread(lock_torture_writer,
					     writer_tasks[i]);
		kfree(writer_tasks);
		writer_tasks = NULL;
	}

	if (reader_tasks) {
		for (i = 0; i < cxt.nrealreaders_stress; i++)
			torture_stop_kthread(lock_torture_reader,
					     reader_tasks[i]);
		kfree(reader_tasks);
		reader_tasks = NULL;
	}

	torture_stop_kthread(lock_torture_stats, stats_task);
	lock_torture_stats_print();  /* -After- the stats thread is stopped! */

	if (atomic_read(&cxt.n_lock_torture_errors))
		lock_torture_print_module_parms(cxt.cur_ops,
						"End of test: FAILURE");
	else if (torture_onoff_failures())
		lock_torture_print_module_parms(cxt.cur_ops,
						"End of test: LOCK_HOTPLUG");
	else
		lock_torture_print_module_parms(cxt.cur_ops,
						"End of test: SUCCESS");

	kfree(cxt.lwsa);
	cxt.lwsa = NULL;
	kfree(cxt.lrsa);
	cxt.lrsa = NULL;

end:
	torture_cleanup_end();
}