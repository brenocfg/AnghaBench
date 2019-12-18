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
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ITEMS ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XA_MARK_0 ; 
 int /*<<< orphan*/  XA_MARK_1 ; 
 int /*<<< orphan*/  XA_MARK_2 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  check_copied_tags (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  item_insert (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 scalar_t__ item_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  item_tag_set (int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long rand () ; 
 unsigned long tag_tagged_items (int /*<<< orphan*/ *,unsigned long,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree ; 
 int /*<<< orphan*/  verify_tag_consistency (int /*<<< orphan*/ *,int) ; 

void copy_tag_check(void)
{
	RADIX_TREE(tree, GFP_KERNEL);
	unsigned long idx[ITEMS];
	unsigned long start, end, count = 0, tagged, cur, tmp;
	int i;

//	printf("generating radix tree indices...\n");
	start = rand();
	end = rand();
	if (start > end && (rand() % 10)) {
		cur = start;
		start = end;
		end = cur;
	}
	/* Specifically create items around the start and the end of the range
	 * with high probability to check for off by one errors */
	cur = rand();
	if (cur & 1) {
		item_insert(&tree, start);
		if (cur & 2) {
			if (start <= end)
				count++;
			item_tag_set(&tree, start, 0);
		}
	}
	if (cur & 4) {
		item_insert(&tree, start-1);
		if (cur & 8)
			item_tag_set(&tree, start-1, 0);
	}
	if (cur & 16) {
		item_insert(&tree, end);
		if (cur & 32) {
			if (start <= end)
				count++;
			item_tag_set(&tree, end, 0);
		}
	}
	if (cur & 64) {
		item_insert(&tree, end+1);
		if (cur & 128)
			item_tag_set(&tree, end+1, 0);
	}

	for (i = 0; i < ITEMS; i++) {
		do {
			idx[i] = rand();
		} while (item_lookup(&tree, idx[i]));

		item_insert(&tree, idx[i]);
		if (rand() & 1) {
			item_tag_set(&tree, idx[i], 0);
			if (idx[i] >= start && idx[i] <= end)
				count++;
		}
/*		if (i % 1000 == 0)
			putchar('.'); */
	}

//	printf("\ncopying tags...\n");
	tagged = tag_tagged_items(&tree, start, end, ITEMS, XA_MARK_0, XA_MARK_1);

//	printf("checking copied tags\n");
	assert(tagged == count);
	check_copied_tags(&tree, start, end, idx, ITEMS, 0, 1);

	/* Copy tags in several rounds */
//	printf("\ncopying tags...\n");
	tmp = rand() % (count / 10 + 2);
	tagged = tag_tagged_items(&tree, start, end, tmp, XA_MARK_0, XA_MARK_2);
	assert(tagged == count);

//	printf("%lu %lu %lu\n", tagged, tmp, count);
//	printf("checking copied tags\n");
	check_copied_tags(&tree, start, end, idx, ITEMS, 0, 2);
	verify_tag_consistency(&tree, 0);
	verify_tag_consistency(&tree, 1);
	verify_tag_consistency(&tree, 2);
//	printf("\n");
	item_kill_tree(&tree);
}