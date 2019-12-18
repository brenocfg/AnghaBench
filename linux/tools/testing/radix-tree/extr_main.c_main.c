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
 int /*<<< orphan*/  benchmark () ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  iteration_test (int,int) ; 
 int /*<<< orphan*/  nr_allocated ; 
 int /*<<< orphan*/  optarg ; 
 int /*<<< orphan*/  preempt_count ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printv (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_cpu_dead (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radix_tree_init () ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 int /*<<< orphan*/  regression1_test () ; 
 int /*<<< orphan*/  regression2_test () ; 
 int /*<<< orphan*/  regression3_test () ; 
 int /*<<< orphan*/  regression4_test () ; 
 int /*<<< orphan*/  single_thread_tests (int) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 unsigned int strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_verbose ; 
 unsigned int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xarray_tests () ; 

int main(int argc, char **argv)
{
	bool long_run = false;
	int opt;
	unsigned int seed = time(NULL);

	while ((opt = getopt(argc, argv, "ls:v")) != -1) {
		if (opt == 'l')
			long_run = true;
		else if (opt == 's')
			seed = strtoul(optarg, NULL, 0);
		else if (opt == 'v')
			test_verbose++;
	}

	printf("random seed %u\n", seed);
	srand(seed);

	printf("running tests\n");

	rcu_register_thread();
	radix_tree_init();

	xarray_tests();
	regression1_test();
	regression2_test();
	regression3_test();
	regression4_test();
	iteration_test(0, 10 + 90 * long_run);
	iteration_test(7, 10 + 90 * long_run);
	single_thread_tests(long_run);

	/* Free any remaining preallocated nodes */
	radix_tree_cpu_dead(0);

	benchmark();

	rcu_barrier();
	printv(2, "after rcu_barrier: %d allocated, preempt %d\n",
		nr_allocated, preempt_count);
	rcu_unregister_thread();

	printf("tests completed\n");

	exit(0);
}