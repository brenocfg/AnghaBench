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
struct rb_root {int dummy; } ;
struct rb_node {scalar_t__ rb_right; scalar_t__ rb_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rb_change_child_rcu (struct rb_node*,struct rb_node*,struct rb_node*,struct rb_root*) ; 
 struct rb_node* rb_parent (struct rb_node*) ; 
 int /*<<< orphan*/  rb_set_parent (scalar_t__,struct rb_node*) ; 

void rb_replace_node_rcu(struct rb_node *victim, struct rb_node *new,
			 struct rb_root *root)
{
	struct rb_node *parent = rb_parent(victim);

	/* Copy the pointers/colour from the victim to the replacement */
	*new = *victim;

	/* Set the surrounding nodes to point to the replacement */
	if (victim->rb_left)
		rb_set_parent(victim->rb_left, new);
	if (victim->rb_right)
		rb_set_parent(victim->rb_right, new);

	/* Set the parent's pointer to the new node last after an RCU barrier
	 * so that the pointers onwards are seen to be set correctly when doing
	 * an RCU walk over the tree.
	 */
	__rb_change_child_rcu(victim, new, parent, root);
}