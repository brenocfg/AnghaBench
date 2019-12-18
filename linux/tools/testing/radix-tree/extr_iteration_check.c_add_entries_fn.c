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
 int /*<<< orphan*/  array ; 
 int /*<<< orphan*/  my_item_insert (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 int /*<<< orphan*/  test_complete ; 

__attribute__((used)) static void *add_entries_fn(void *arg)
{
	rcu_register_thread();

	while (!test_complete) {
		unsigned long pgoff;

		for (pgoff = 0; pgoff < MAX_IDX; pgoff++) {
			my_item_insert(&array, pgoff);
		}
	}

	rcu_unregister_thread();

	return NULL;
}