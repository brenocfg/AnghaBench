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
struct posix_msg_tree_node {struct rb_node rb_node; } ;
struct mqueue_inode_info {struct posix_msg_tree_node* node_cache; int /*<<< orphan*/  msg_tree; struct rb_node* msg_tree_rightmost; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct posix_msg_tree_node*) ; 
 int /*<<< orphan*/  rb_erase (struct rb_node*,int /*<<< orphan*/ *) ; 
 struct rb_node* rb_prev (struct rb_node*) ; 

__attribute__((used)) static inline void msg_tree_erase(struct posix_msg_tree_node *leaf,
				  struct mqueue_inode_info *info)
{
	struct rb_node *node = &leaf->rb_node;

	if (info->msg_tree_rightmost == node)
		info->msg_tree_rightmost = rb_prev(node);

	rb_erase(node, &info->msg_tree);
	if (info->node_cache) {
		kfree(leaf);
	} else {
		info->node_cache = leaf;
	}
}