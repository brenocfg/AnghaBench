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
 int /*<<< orphan*/  AA ; 
 int /*<<< orphan*/  ABBA ; 
 int /*<<< orphan*/  ABBCCA ; 
 int /*<<< orphan*/  ABBCCDDA ; 
 int /*<<< orphan*/  ABCABC ; 
 int /*<<< orphan*/  ABCDBCDA ; 
 int /*<<< orphan*/  ABCDBDDA ; 
 int /*<<< orphan*/  DO_TESTCASE_2x3 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TESTCASE_2x6 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TESTCASE_6 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TESTCASE_6R (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TESTCASE_6x2 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TESTCASE_6x6 (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DO_TESTCASE_6x6RW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FAILURE ; 
 int /*<<< orphan*/  LOCKTYPE_RWLOCK ; 
 int /*<<< orphan*/  LOCKTYPE_RWSEM ; 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/ * current ; 
 int debug_locks ; 
 int debug_locks_silent ; 
 int /*<<< orphan*/  debug_locks_verbose ; 
 int /*<<< orphan*/  dotest (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_unlock ; 
 scalar_t__ expected_testcase_failures ; 
 int /*<<< orphan*/  init_held ; 
 int /*<<< orphan*/  init_shared_classes () ; 
 int /*<<< orphan*/  irq_inversion ; 
 int /*<<< orphan*/  irq_read_recursion ; 
 int /*<<< orphan*/  irqsafe1 ; 
 int /*<<< orphan*/  irqsafe2A ; 
 int /*<<< orphan*/  irqsafe2B ; 
 int /*<<< orphan*/  irqsafe3 ; 
 int /*<<< orphan*/  irqsafe4 ; 
 int /*<<< orphan*/  lockdep_set_selftest_task (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_cont (char*) ; 
 int /*<<< orphan*/  print_testname (char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  rlock_AA1 ; 
 int /*<<< orphan*/  rlock_AA1B ; 
 int /*<<< orphan*/  rlock_AA2 ; 
 int /*<<< orphan*/  rlock_AA3 ; 
 int /*<<< orphan*/  rlock_ABBA1 ; 
 int /*<<< orphan*/  rlock_ABBA2 ; 
 int /*<<< orphan*/  rlock_ABBA3 ; 
 int /*<<< orphan*/  rsem_AA1 ; 
 int /*<<< orphan*/  rsem_AA1B ; 
 int /*<<< orphan*/  rsem_AA2 ; 
 int /*<<< orphan*/  rsem_AA3 ; 
 int /*<<< orphan*/  rwsem_ABBA1 ; 
 int /*<<< orphan*/  rwsem_ABBA2 ; 
 int /*<<< orphan*/  rwsem_ABBA3 ; 
 scalar_t__ testcase_successes ; 
 int /*<<< orphan*/  testcase_total ; 
 scalar_t__ unexpected_testcase_failures ; 
 int /*<<< orphan*/  ww_tests () ; 

void locking_selftest(void)
{
	/*
	 * Got a locking failure before the selftest ran?
	 */
	if (!debug_locks) {
		printk("----------------------------------\n");
		printk("| Locking API testsuite disabled |\n");
		printk("----------------------------------\n");
		return;
	}

	/*
	 * Run the testsuite:
	 */
	printk("------------------------\n");
	printk("| Locking API testsuite:\n");
	printk("----------------------------------------------------------------------------\n");
	printk("                                 | spin |wlock |rlock |mutex | wsem | rsem |\n");
	printk("  --------------------------------------------------------------------------\n");

	init_shared_classes();
	debug_locks_silent = !debug_locks_verbose;
	lockdep_set_selftest_task(current);

	DO_TESTCASE_6R("A-A deadlock", AA);
	DO_TESTCASE_6R("A-B-B-A deadlock", ABBA);
	DO_TESTCASE_6R("A-B-B-C-C-A deadlock", ABBCCA);
	DO_TESTCASE_6R("A-B-C-A-B-C deadlock", ABCABC);
	DO_TESTCASE_6R("A-B-B-C-C-D-D-A deadlock", ABBCCDDA);
	DO_TESTCASE_6R("A-B-C-D-B-D-D-A deadlock", ABCDBDDA);
	DO_TESTCASE_6R("A-B-C-D-B-C-D-A deadlock", ABCDBCDA);
	DO_TESTCASE_6("double unlock", double_unlock);
	DO_TESTCASE_6("initialize held", init_held);

	printk("  --------------------------------------------------------------------------\n");
	print_testname("recursive read-lock");
	pr_cont("             |");
	dotest(rlock_AA1, SUCCESS, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	dotest(rsem_AA1, FAILURE, LOCKTYPE_RWSEM);
	pr_cont("\n");

	print_testname("recursive read-lock #2");
	pr_cont("             |");
	dotest(rlock_AA1B, SUCCESS, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	dotest(rsem_AA1B, FAILURE, LOCKTYPE_RWSEM);
	pr_cont("\n");

	print_testname("mixed read-write-lock");
	pr_cont("             |");
	dotest(rlock_AA2, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	dotest(rsem_AA2, FAILURE, LOCKTYPE_RWSEM);
	pr_cont("\n");

	print_testname("mixed write-read-lock");
	pr_cont("             |");
	dotest(rlock_AA3, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	dotest(rsem_AA3, FAILURE, LOCKTYPE_RWSEM);
	pr_cont("\n");

	print_testname("mixed read-lock/lock-write ABBA");
	pr_cont("             |");
	dotest(rlock_ABBA1, FAILURE, LOCKTYPE_RWLOCK);
#ifdef CONFIG_PROVE_LOCKING
	/*
	 * Lockdep does indeed fail here, but there's nothing we can do about
	 * that now.  Don't kill lockdep for it.
	 */
	unexpected_testcase_failures--;
#endif

	pr_cont("             |");
	dotest(rwsem_ABBA1, FAILURE, LOCKTYPE_RWSEM);

	print_testname("mixed read-lock/lock-read ABBA");
	pr_cont("             |");
	dotest(rlock_ABBA2, SUCCESS, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	dotest(rwsem_ABBA2, FAILURE, LOCKTYPE_RWSEM);

	print_testname("mixed write-lock/lock-write ABBA");
	pr_cont("             |");
	dotest(rlock_ABBA3, FAILURE, LOCKTYPE_RWLOCK);
	pr_cont("             |");
	dotest(rwsem_ABBA3, FAILURE, LOCKTYPE_RWSEM);

	printk("  --------------------------------------------------------------------------\n");

	/*
	 * irq-context testcases:
	 */
	DO_TESTCASE_2x6("irqs-on + irq-safe-A", irqsafe1);
	DO_TESTCASE_2x3("sirq-safe-A => hirqs-on", irqsafe2A);
	DO_TESTCASE_2x6("safe-A + irqs-on", irqsafe2B);
	DO_TESTCASE_6x6("safe-A + unsafe-B #1", irqsafe3);
	DO_TESTCASE_6x6("safe-A + unsafe-B #2", irqsafe4);
	DO_TESTCASE_6x6RW("irq lock-inversion", irq_inversion);

	DO_TESTCASE_6x2("irq read-recursion", irq_read_recursion);
//	DO_TESTCASE_6x2B("irq read-recursion #2", irq_read_recursion2);

	ww_tests();

	if (unexpected_testcase_failures) {
		printk("-----------------------------------------------------------------\n");
		debug_locks = 0;
		printk("BUG: %3d unexpected failures (out of %3d) - debugging disabled! |\n",
			unexpected_testcase_failures, testcase_total);
		printk("-----------------------------------------------------------------\n");
	} else if (expected_testcase_failures && testcase_successes) {
		printk("--------------------------------------------------------\n");
		printk("%3d out of %3d testcases failed, as expected. |\n",
			expected_testcase_failures, testcase_total);
		printk("----------------------------------------------------\n");
		debug_locks = 1;
	} else if (expected_testcase_failures && !testcase_successes) {
		printk("--------------------------------------------------------\n");
		printk("All %3d testcases failed, as expected. |\n",
			expected_testcase_failures);
		printk("----------------------------------------\n");
		debug_locks = 1;
	} else {
		printk("-------------------------------------------------------\n");
		printk("Good, all %3d testcases passed! |\n",
			testcase_successes);
		printk("---------------------------------\n");
		debug_locks = 1;
	}
	lockdep_set_selftest_task(NULL);
	debug_locks_silent = 0;
}