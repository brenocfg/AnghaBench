#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t index; } ;
struct test_parman_item {int used; TYPE_2__ parman_item; TYPE_1__* prio; } ;
struct test_parman {int /*<<< orphan*/  used_items; int /*<<< orphan*/  parman; struct test_parman_item** prio_array; scalar_t__ bulk_noop; struct test_parman_item* items; } ;
struct TYPE_4__ {int /*<<< orphan*/  parman_prio; } ;

/* Variables and functions */
 unsigned int TEST_PARMAN_ITEM_MASK ; 
 int parman_item_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  parman_item_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 unsigned int test_parman_rnd_get (struct test_parman*) ; 
 scalar_t__ test_parman_run_check_budgets (struct test_parman*) ; 

__attribute__((used)) static int test_parman_run(struct test_parman *test_parman)
{
	unsigned int i = test_parman_rnd_get(test_parman);
	int err;

	while (test_parman_run_check_budgets(test_parman)) {
		unsigned int item_index = i++ & TEST_PARMAN_ITEM_MASK;
		struct test_parman_item *item = &test_parman->items[item_index];

		if (test_parman->bulk_noop)
			continue;

		if (!item->used) {
			err = parman_item_add(test_parman->parman,
					      &item->prio->parman_prio,
					      &item->parman_item);
			if (err)
				return err;
			test_parman->prio_array[item->parman_item.index] = item;
			test_parman->used_items++;
		} else {
			test_parman->prio_array[item->parman_item.index] = NULL;
			parman_item_remove(test_parman->parman,
					   &item->prio->parman_prio,
					   &item->parman_item);
			test_parman->used_items--;
		}
		item->used = !item->used;
	}
	return 0;
}