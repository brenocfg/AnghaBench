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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SC_NPROCESSORS_ONLN ; 
 int /*<<< orphan*/  creator_func ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iterator_func ; 
 int /*<<< orphan*/  pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int sysconf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void multiorder_iteration_race(void)
{
	const int num_threads = sysconf(_SC_NPROCESSORS_ONLN);
	pthread_t worker_thread[num_threads];
	RADIX_TREE(tree, GFP_KERNEL);
	int i;

	pthread_create(&worker_thread[0], NULL, &creator_func, &tree);
	for (i = 1; i < num_threads; i++)
		pthread_create(&worker_thread[i], NULL, &iterator_func, &tree);

	for (i = 0; i < num_threads; i++)
		pthread_join(worker_thread[i], NULL);

	item_kill_tree(&tree);
}