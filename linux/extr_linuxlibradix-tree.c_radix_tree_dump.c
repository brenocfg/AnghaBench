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

/* Variables and functions */
 int ROOT_TAG_SHIFT ; 
 int /*<<< orphan*/  dump_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entry_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,struct radix_tree_root*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radix_tree_is_internal_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void radix_tree_dump(struct radix_tree_root *root)
{
	pr_debug("radix root: %p rnode %p tags %x\n",
			root, root->rnode,
			root->gfp_mask >> ROOT_TAG_SHIFT);
	if (!radix_tree_is_internal_node(root->rnode))
		return;
	dump_node(entry_to_node(root->rnode), 0);
}