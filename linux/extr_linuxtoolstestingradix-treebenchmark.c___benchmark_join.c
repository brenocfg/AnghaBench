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
struct timespec {long long tv_sec; long long tv_nsec; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 unsigned long find_item (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* item_create (unsigned long,unsigned int) ; 
 int /*<<< orphan*/  item_insert_order (int /*<<< orphan*/ *,unsigned long,unsigned int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_join (int /*<<< orphan*/ *,unsigned long,unsigned int,void*) ; 
 void* radix_tree_lookup (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static long long  __benchmark_join(unsigned long index,
			     unsigned order1, unsigned order2)
{
	unsigned long loc;
	struct timespec start, finish;
	long long nsec;
	void *item, *item2 = item_create(index + 1, order1);
	RADIX_TREE(tree, GFP_KERNEL);

	item_insert_order(&tree, index, order2);
	item = radix_tree_lookup(&tree, index);

	clock_gettime(CLOCK_MONOTONIC, &start);
	radix_tree_join(&tree, index + 1, order1, item2);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	nsec = (finish.tv_sec - start.tv_sec) * NSEC_PER_SEC +
		(finish.tv_nsec - start.tv_nsec);

	loc = find_item(&tree, item);
	if (loc == -1)
		free(item);

	item_kill_tree(&tree);

	return nsec;
}