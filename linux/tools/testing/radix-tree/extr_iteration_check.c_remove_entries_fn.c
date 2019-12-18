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
struct item {int dummy; } ;

/* Variables and functions */
 int MAX_IDX ; 
 int /*<<< orphan*/  array ; 
 int /*<<< orphan*/  item_free (struct item*,int) ; 
 int rand_r (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu_register_thread () ; 
 int /*<<< orphan*/  rcu_unregister_thread () ; 
 int /*<<< orphan*/ * seeds ; 
 int /*<<< orphan*/  test_complete ; 
 struct item* xa_erase (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void *remove_entries_fn(void *arg)
{
	rcu_register_thread();

	while (!test_complete) {
		int pgoff;
		struct item *item;

		pgoff = rand_r(&seeds[2]) % MAX_IDX;

		item = xa_erase(&array, pgoff);
		if (item)
			item_free(item, pgoff);
	}

	rcu_unregister_thread();

	return NULL;
}