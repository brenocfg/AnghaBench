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
 int MAX_IDX ; 
 int /*<<< orphan*/  item_delete (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int rand_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 int /*<<< orphan*/ * seeds ; 
 int /*<<< orphan*/  test_complete ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  tree_lock ; 

__attribute__((used)) static void *remove_entries_fn(void *arg)
{
	rcu_register_thread();

	while (!test_complete) {
		int pgoff;

		pgoff = rand_r(&seeds[2]) % MAX_IDX;

		pthread_mutex_lock(&tree_lock);
		item_delete(&tree, pgoff);
		pthread_mutex_unlock(&tree_lock);
	}

	rcu_unregister_thread();

	return NULL;
}