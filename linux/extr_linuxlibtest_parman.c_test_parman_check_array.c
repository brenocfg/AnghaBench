#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int index; } ;
struct test_parman_item {TYPE_2__ parman_item; TYPE_1__* prio; } ;
struct test_parman {unsigned int prio_array_limit; unsigned int used_items; struct test_parman_item** prio_array; } ;
struct TYPE_3__ {unsigned long priority; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int TEST_PARMAN_BASE_COUNT ; 
 unsigned int TEST_PARMAN_RESIZE_STEP_COUNT ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*) ; 

__attribute__((used)) static int test_parman_check_array(struct test_parman *test_parman,
				   bool gaps_allowed)
{
	unsigned int last_unused_items = 0;
	unsigned long last_priority = 0;
	unsigned int used_items = 0;
	int i;

	if (test_parman->prio_array_limit < TEST_PARMAN_BASE_COUNT) {
		pr_err("Array limit is lower than the base count (%lu < %lu)\n",
		       test_parman->prio_array_limit, TEST_PARMAN_BASE_COUNT);
		return -EINVAL;
	}

	for (i = 0; i < test_parman->prio_array_limit; i++) {
		struct test_parman_item *item = test_parman->prio_array[i];

		if (!item) {
			last_unused_items++;
			continue;
		}
		if (last_unused_items && !gaps_allowed) {
			pr_err("Gap found in array even though they are forbidden\n");
			return -EINVAL;
		}

		last_unused_items = 0;
		used_items++;

		if (item->prio->priority < last_priority) {
			pr_err("Item belongs under higher priority then the last one (current: %lu, previous: %lu)\n",
			       item->prio->priority, last_priority);
			return -EINVAL;
		}
		last_priority = item->prio->priority;

		if (item->parman_item.index != i) {
			pr_err("Item has different index in compare to where it actually is (%lu != %d)\n",
			       item->parman_item.index, i);
			return -EINVAL;
		}
	}

	if (used_items != test_parman->used_items) {
		pr_err("Number of used items in array does not match (%u != %u)\n",
		       used_items, test_parman->used_items);
		return -EINVAL;
	}

	if (last_unused_items >= TEST_PARMAN_RESIZE_STEP_COUNT) {
		pr_err("Number of unused item at the end of array is bigger than resize step (%u >= %lu)\n",
		       last_unused_items, TEST_PARMAN_RESIZE_STEP_COUNT);
		return -EINVAL;
	}

	pr_info("Priority array check successful\n");

	return 0;
}