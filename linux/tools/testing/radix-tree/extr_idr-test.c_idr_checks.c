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
struct item {unsigned int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE_IDR (int /*<<< orphan*/ ) ; 
 struct item* DUMMY_PTR ; 
 unsigned long ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long INT_MAX ; 
 unsigned long RADIX_TREE_MAP_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  idr ; 
 int /*<<< orphan*/  idr_align_test (int /*<<< orphan*/ *) ; 
 unsigned long idr_alloc (int /*<<< orphan*/ *,struct item*,int,int,int /*<<< orphan*/ ) ; 
 unsigned int idr_alloc_cyclic (int /*<<< orphan*/ *,struct item*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_alloc_test () ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_find_test () ; 
 int /*<<< orphan*/  idr_for_each (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_get_next_test (int) ; 
 int idr_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idr_nowait_test () ; 
 int /*<<< orphan*/  idr_null_test () ; 
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  idr_replace_test () ; 
 int /*<<< orphan*/  idr_set_cursor (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  idr_u32_test (int) ; 
 struct item* item_create (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  item_idr_free ; 
 int /*<<< orphan*/  item_idr_remove (int /*<<< orphan*/ *,unsigned long) ; 

void idr_checks(void)
{
	unsigned long i;
	DEFINE_IDR(idr);

	for (i = 0; i < 10000; i++) {
		struct item *item = item_create(i, 0);
		assert(idr_alloc(&idr, item, 0, 20000, GFP_KERNEL) == i);
	}

	assert(idr_alloc(&idr, DUMMY_PTR, 5, 30, GFP_KERNEL) < 0);

	for (i = 0; i < 5000; i++)
		item_idr_remove(&idr, i);

	idr_remove(&idr, 3);

	idr_for_each(&idr, item_idr_free, &idr);
	idr_destroy(&idr);

	assert(idr_is_empty(&idr));

	idr_remove(&idr, 3);
	idr_remove(&idr, 0);

	assert(idr_alloc(&idr, DUMMY_PTR, 0, 0, GFP_KERNEL) == 0);
	idr_remove(&idr, 1);
	for (i = 1; i < RADIX_TREE_MAP_SIZE; i++)
		assert(idr_alloc(&idr, DUMMY_PTR, 0, 0, GFP_KERNEL) == i);
	idr_remove(&idr, 1 << 30);
	idr_destroy(&idr);

	for (i = INT_MAX - 3UL; i < INT_MAX + 1UL; i++) {
		struct item *item = item_create(i, 0);
		assert(idr_alloc(&idr, item, i, i + 10, GFP_KERNEL) == i);
	}
	assert(idr_alloc(&idr, DUMMY_PTR, i - 2, i, GFP_KERNEL) == -ENOSPC);
	assert(idr_alloc(&idr, DUMMY_PTR, i - 2, i + 10, GFP_KERNEL) == -ENOSPC);

	idr_for_each(&idr, item_idr_free, &idr);
	idr_destroy(&idr);
	idr_destroy(&idr);

	assert(idr_is_empty(&idr));

	idr_set_cursor(&idr, INT_MAX - 3UL);
	for (i = INT_MAX - 3UL; i < INT_MAX + 3UL; i++) {
		struct item *item;
		unsigned int id;
		if (i <= INT_MAX)
			item = item_create(i, 0);
		else
			item = item_create(i - INT_MAX - 1, 0);

		id = idr_alloc_cyclic(&idr, item, 0, 0, GFP_KERNEL);
		assert(id == item->index);
	}

	idr_for_each(&idr, item_idr_free, &idr);
	idr_destroy(&idr);
	assert(idr_is_empty(&idr));

	for (i = 1; i < 10000; i++) {
		struct item *item = item_create(i, 0);
		assert(idr_alloc(&idr, item, 1, 20000, GFP_KERNEL) == i);
	}

	idr_for_each(&idr, item_idr_free, &idr);
	idr_destroy(&idr);

	idr_replace_test();
	idr_alloc_test();
	idr_null_test();
	idr_nowait_test();
	idr_get_next_test(0);
	idr_get_next_test(1);
	idr_get_next_test(4);
	idr_u32_test(4);
	idr_u32_test(1);
	idr_u32_test(0);
	idr_align_test(&idr);
	idr_find_test();
}