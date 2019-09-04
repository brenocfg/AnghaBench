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
 int /*<<< orphan*/  GFP_ATOMIC ; 
 long long NSEC_PER_SEC ; 
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 
 int /*<<< orphan*/  item_insert_order (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radix_tree_split (int /*<<< orphan*/ *,unsigned long,int) ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static long long  __benchmark_split(unsigned long index,
				    int old_order, int new_order)
{
	struct timespec start, finish;
	long long nsec;
	RADIX_TREE(tree, GFP_ATOMIC);

	item_insert_order(&tree, index, old_order);

	clock_gettime(CLOCK_MONOTONIC, &start);
	radix_tree_split(&tree, index, new_order);
	clock_gettime(CLOCK_MONOTONIC, &finish);
	nsec = (finish.tv_sec - start.tv_sec) * NSEC_PER_SEC +
	       (finish.tv_nsec - start.tv_nsec);

	item_kill_tree(&tree);

	return nsec;

}