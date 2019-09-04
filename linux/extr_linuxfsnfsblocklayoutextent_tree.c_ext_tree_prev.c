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
struct rb_node {int dummy; } ;
struct pnfs_block_extent {int /*<<< orphan*/  be_node; } ;

/* Variables and functions */
 struct pnfs_block_extent* ext_node (struct rb_node*) ; 
 struct rb_node* rb_prev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct pnfs_block_extent *
ext_tree_prev(struct pnfs_block_extent *be)
{
	struct rb_node *node = rb_prev(&be->be_node);
	return node ? ext_node(node) : NULL;
}