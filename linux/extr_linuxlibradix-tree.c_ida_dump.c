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
struct radix_tree_root {int gfp_mask; int /*<<< orphan*/  rnode; } ;
struct ida {struct radix_tree_root ida_rt; } ;

/* Variables and functions */
 int ROOT_TAG_SHIFT ; 
 int /*<<< orphan*/  dump_ida_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct ida*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ida_dump(struct ida *ida)
{
	struct radix_tree_root *root = &ida->ida_rt;
	pr_debug("ida: %p node %p free %d\n", ida, root->rnode,
				root->gfp_mask >> ROOT_TAG_SHIFT);
	dump_ida_node(root->rnode, 0);
}