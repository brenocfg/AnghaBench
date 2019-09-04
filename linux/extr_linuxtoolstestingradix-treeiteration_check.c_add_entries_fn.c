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
 unsigned long MAX_IDX ; 
 int /*<<< orphan*/  TAG ; 
 scalar_t__ item_insert_order (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  item_tag_set (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 int max_order ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 int /*<<< orphan*/  test_complete ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  tree_lock ; 

__attribute__((used)) static void *add_entries_fn(void *arg)
{
	rcu_register_thread();

	while (!test_complete) {
		unsigned long pgoff;
		int order;

		for (pgoff = 0; pgoff < MAX_IDX; pgoff++) {
			pthread_mutex_lock(&tree_lock);
			for (order = max_order; order >= 0; order--) {
				if (item_insert_order(&tree, pgoff, order)
						== 0) {
					item_tag_set(&tree, pgoff, TAG);
					break;
				}
			}
			pthread_mutex_unlock(&tree_lock);
		}
	}

	rcu_unregister_thread();

	return NULL;
}