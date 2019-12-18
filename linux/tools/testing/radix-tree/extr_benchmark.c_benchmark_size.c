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
 int /*<<< orphan*/  benchmark_delete (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  benchmark_insert (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 long long benchmark_iter (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  benchmark_tagging (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  item_kill_tree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printv (int,char*,unsigned long,unsigned long,long long) ; 
 int /*<<< orphan*/  rcu_barrier () ; 
 int /*<<< orphan*/  tree ; 

__attribute__((used)) static void benchmark_size(unsigned long size, unsigned long step)
{
	RADIX_TREE(tree, GFP_KERNEL);
	long long normal, tagged;

	benchmark_insert(&tree, size, step);
	benchmark_tagging(&tree, size, step);

	tagged = benchmark_iter(&tree, true);
	normal = benchmark_iter(&tree, false);

	printv(2, "Size: %8ld, step: %8ld, tagged iteration: %8lld ns\n",
		size, step, tagged);
	printv(2, "Size: %8ld, step: %8ld, normal iteration: %8lld ns\n",
		size, step, normal);

	benchmark_delete(&tree, size, step);

	item_kill_tree(&tree);
	rcu_barrier();
}