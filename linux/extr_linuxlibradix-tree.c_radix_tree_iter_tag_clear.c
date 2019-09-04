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
struct radix_tree_root {int dummy; } ;
struct radix_tree_iter {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  iter_offset (struct radix_tree_iter const*) ; 
 int /*<<< orphan*/  node_tag_clear (struct radix_tree_root*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

void radix_tree_iter_tag_clear(struct radix_tree_root *root,
			const struct radix_tree_iter *iter, unsigned int tag)
{
	node_tag_clear(root, iter->node, tag, iter_offset(iter));
}