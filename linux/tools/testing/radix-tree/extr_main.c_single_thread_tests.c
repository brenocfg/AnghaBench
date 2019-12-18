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
 int /*<<< orphan*/  add_and_check () ; 
 int /*<<< orphan*/  big_gang_check (int) ; 
 int /*<<< orphan*/  copy_tag_check () ; 
 int /*<<< orphan*/  dynamic_height_check () ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gang_check () ; 
 int /*<<< orphan*/  ida_tests () ; 
 int /*<<< orphan*/  idr_checks () ; 
 int /*<<< orphan*/  multiorder_checks () ; 
 int /*<<< orphan*/  nr_allocated ; 
 int /*<<< orphan*/  preempt_count ; 
 int /*<<< orphan*/  printv (int,char*,int,...) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  tag_check () ; 

__attribute__((used)) static void single_thread_tests(bool long_run)
{
	int i;

	printv(1, "starting single_thread_tests: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	multiorder_checks();
	rcu_barrier();
	printv(2, "after multiorder_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	tag_check();
	rcu_barrier();
	printv(2, "after tag_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	gang_check();
	rcu_barrier();
	printv(2, "after gang_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	add_and_check();
	rcu_barrier();
	printv(2, "after add_and_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	dynamic_height_check();
	rcu_barrier();
	printv(2, "after dynamic_height_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	idr_checks();
	ida_tests();
	rcu_barrier();
	printv(2, "after idr_checks: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	big_gang_check(long_run);
	rcu_barrier();
	printv(2, "after big_gang_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	for (i = 0; i < (long_run ? 2000 : 3); i++) {
		copy_tag_check();
		printv(2, "%d ", i);
		fflush(stdout);
	}
	rcu_barrier();
	printv(2, "after copy_tag_check: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
}