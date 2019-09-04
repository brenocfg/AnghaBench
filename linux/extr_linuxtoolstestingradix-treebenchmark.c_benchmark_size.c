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
 int /*<<< orphan*/  RADIX_TREE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  benchmark_delete (int /*<<< orphan*/ *,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  benchmark_insert (int /*<<< orphan*/ *,unsigned long,unsigned long,int) ; 
 long long benchmark_iter (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  benchmark_tagging (int /*<<< orphan*/ *,unsigned long,unsigned long,int) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printv (int,char*,unsigned long,unsigned long,int,long long) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void benchmark_size(unsigned long size, unsigned long step, int order)
{
	RADIX_TREE(tree, GFP_KERNEL);
	long long normal, tagged;

	benchmark_insert(&tree, size, step, order);
	benchmark_tagging(&tree, size, step, order);

	tagged = benchmark_iter(&tree, true);
	normal = benchmark_iter(&tree, false);

	printv(2, "Size: %8ld, step: %8ld, order: %d, tagged iteration: %8lld ns\n",
		size, step, order, tagged);
	printv(2, "Size: %8ld, step: %8ld, order: %d, normal iteration: %8lld ns\n",
		size, step, order, normal);

	benchmark_delete(&tree, size, step, order);

	item_kill_tree(&tree);
	rcu_barrier();
}