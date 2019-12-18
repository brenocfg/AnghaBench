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
 int NUM_THREADS ; 
 int /*<<< orphan*/  add_entries_fn ; 
 int /*<<< orphan*/  array ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 unsigned int max_order ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printv (int,char*,char*,unsigned int) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rand () ; 
 int /*<<< orphan*/  remove_entries_fn ; 
 int /*<<< orphan*/ * seeds ; 
 int /*<<< orphan*/  sleep (unsigned int) ; 
 int /*<<< orphan*/  tag_entries_fn ; 
 int /*<<< orphan*/  tagged_iteration_fn ; 
 int test_complete ; 
 int /*<<< orphan*/ * threads ; 
 int /*<<< orphan*/  untagged_iteration_fn ; 

void iteration_test(unsigned order, unsigned test_duration)
{
	int i;

	printv(1, "Running %siteration tests for %d seconds\n",
			order > 0 ? "multiorder " : "", test_duration);

	max_order = order;
	test_complete = false;

	for (i = 0; i < 3; i++)
		seeds[i] = rand();

	if (pthread_create(&threads[0], NULL, tagged_iteration_fn, NULL)) {
		perror("create tagged iteration thread");
		exit(1);
	}
	if (pthread_create(&threads[1], NULL, untagged_iteration_fn, NULL)) {
		perror("create untagged iteration thread");
		exit(1);
	}
	if (pthread_create(&threads[2], NULL, add_entries_fn, NULL)) {
		perror("create add entry thread");
		exit(1);
	}
	if (pthread_create(&threads[3], NULL, remove_entries_fn, NULL)) {
		perror("create remove entry thread");
		exit(1);
	}
	if (pthread_create(&threads[4], NULL, tag_entries_fn, NULL)) {
		perror("create tag entry thread");
		exit(1);
	}

	sleep(test_duration);
	test_complete = true;

	for (i = 0; i < NUM_THREADS; i++) {
		if (pthread_join(threads[i], NULL)) {
			perror("pthread_join");
			exit(1);
		}
	}

	item_kill_tree(&array);
}