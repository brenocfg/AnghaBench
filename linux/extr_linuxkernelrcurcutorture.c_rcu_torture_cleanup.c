#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* cleanup ) () ;int /*<<< orphan*/  (* cb_barrier ) () ;int /*<<< orphan*/  name; int /*<<< orphan*/  ttype; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cbflood_task ; 
 int /*<<< orphan*/  cpuhp_remove_state (int /*<<< orphan*/ ) ; 
 TYPE_1__* cur_ops ; 
 int /*<<< orphan*/ * fakewriter_tasks ; 
 int /*<<< orphan*/  fqs_task ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 scalar_t__ n_rcu_torture_barrier_error ; 
 int /*<<< orphan*/  n_rcu_torture_error ; 
 int ncbflooders ; 
 int nfakewriters ; 
 int nrealreaders ; 
 int /*<<< orphan*/  pr_alert (char*,int /*<<< orphan*/ ,unsigned long,int) ; 
 int /*<<< orphan*/  rcu_torture_barrier_cleanup () ; 
 scalar_t__ rcu_torture_can_boost () ; 
 int /*<<< orphan*/  rcu_torture_cbflood ; 
 int /*<<< orphan*/ * rcu_torture_current ; 
 int /*<<< orphan*/  rcu_torture_fakewriter ; 
 int /*<<< orphan*/  rcu_torture_fqs ; 
 int /*<<< orphan*/  rcu_torture_print_module_parms (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  rcu_torture_reader ; 
 int /*<<< orphan*/  rcu_torture_stall ; 
 int /*<<< orphan*/  rcu_torture_stats ; 
 int /*<<< orphan*/  rcu_torture_stats_print () ; 
 int /*<<< orphan*/  rcu_torture_writer ; 
 int /*<<< orphan*/  rcutor_hp ; 
 int /*<<< orphan*/  rcutorture_get_gp_data (int /*<<< orphan*/ ,int*,unsigned long*) ; 
 int /*<<< orphan*/ * reader_tasks ; 
 int /*<<< orphan*/  srcu_ctlp ; 
 int /*<<< orphan*/  srcutorture_get_gp_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,unsigned long*) ; 
 int /*<<< orphan*/  stall_task ; 
 int /*<<< orphan*/  stats_task ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 () ; 
 int /*<<< orphan*/  stub3 () ; 
 scalar_t__ torture_cleanup_begin () ; 
 int /*<<< orphan*/  torture_cleanup_end () ; 
 scalar_t__ torture_onoff_failures () ; 
 int /*<<< orphan*/  torture_stop_kthread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writer_task ; 

__attribute__((used)) static void
rcu_torture_cleanup(void)
{
	int flags = 0;
	unsigned long gp_seq = 0;
	int i;

	if (torture_cleanup_begin()) {
		if (cur_ops->cb_barrier != NULL)
			cur_ops->cb_barrier();
		return;
	}

	rcu_torture_barrier_cleanup();
	torture_stop_kthread(rcu_torture_stall, stall_task);
	torture_stop_kthread(rcu_torture_writer, writer_task);

	if (reader_tasks) {
		for (i = 0; i < nrealreaders; i++)
			torture_stop_kthread(rcu_torture_reader,
					     reader_tasks[i]);
		kfree(reader_tasks);
	}
	rcu_torture_current = NULL;

	if (fakewriter_tasks) {
		for (i = 0; i < nfakewriters; i++) {
			torture_stop_kthread(rcu_torture_fakewriter,
					     fakewriter_tasks[i]);
		}
		kfree(fakewriter_tasks);
		fakewriter_tasks = NULL;
	}

	rcutorture_get_gp_data(cur_ops->ttype, &flags, &gp_seq);
	srcutorture_get_gp_data(cur_ops->ttype, srcu_ctlp, &flags, &gp_seq);
	pr_alert("%s:  End-test grace-period state: g%lu f%#x\n",
		 cur_ops->name, gp_seq, flags);
	torture_stop_kthread(rcu_torture_stats, stats_task);
	torture_stop_kthread(rcu_torture_fqs, fqs_task);
	for (i = 0; i < ncbflooders; i++)
		torture_stop_kthread(rcu_torture_cbflood, cbflood_task[i]);
	if (rcu_torture_can_boost())
		cpuhp_remove_state(rcutor_hp);

	/*
	 * Wait for all RCU callbacks to fire, then do flavor-specific
	 * cleanup operations.
	 */
	if (cur_ops->cb_barrier != NULL)
		cur_ops->cb_barrier();
	if (cur_ops->cleanup != NULL)
		cur_ops->cleanup();

	rcu_torture_stats_print();  /* -After- the stats thread is stopped! */

	if (atomic_read(&n_rcu_torture_error) || n_rcu_torture_barrier_error)
		rcu_torture_print_module_parms(cur_ops, "End of test: FAILURE");
	else if (torture_onoff_failures())
		rcu_torture_print_module_parms(cur_ops,
					       "End of test: RCU_HOTPLUG");
	else
		rcu_torture_print_module_parms(cur_ops, "End of test: SUCCESS");
	torture_cleanup_end();
}