#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct test_parman_item {int /*<<< orphan*/  parman_item; TYPE_1__* prio; int /*<<< orphan*/  used; } ;
struct test_parman {int /*<<< orphan*/  parman; struct test_parman_item* items; } ;
struct TYPE_2__ {int /*<<< orphan*/  parman_prio; } ;

/* Variables and functions */
 int TEST_PARMAN_ITEM_COUNT ; 
 int /*<<< orphan*/  parman_item_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_parman_items_fini(struct test_parman *test_parman)
{
	int i;

	for (i = 0; i < TEST_PARMAN_ITEM_COUNT; i++) {
		struct test_parman_item *item = &test_parman->items[i];

		if (!item->used)
			continue;
		parman_item_remove(test_parman->parman,
				   &item->prio->parman_prio,
				   &item->parman_item);
	}
}