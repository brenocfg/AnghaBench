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
struct kernfs_node {struct kernfs_node* parent; int /*<<< orphan*/  rb; } ;

/* Variables and functions */
 struct kernfs_node* kernfs_leftmost_descendant (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_mutex ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 struct rb_node* rb_next (int /*<<< orphan*/ *) ; 
 struct kernfs_node* rb_to_kn (struct rb_node*) ; 

__attribute__((used)) static struct kernfs_node *kernfs_next_descendant_post(struct kernfs_node *pos,
						       struct kernfs_node *root)
{
	struct rb_node *rbn;

	lockdep_assert_held(&kernfs_mutex);

	/* if first iteration, visit leftmost descendant which may be root */
	if (!pos)
		return kernfs_leftmost_descendant(root);

	/* if we visited @root, we're done */
	if (pos == root)
		return NULL;

	/* if there's an unvisited sibling, visit its leftmost descendant */
	rbn = rb_next(&pos->rb);
	if (rbn)
		return kernfs_leftmost_descendant(rb_to_kn(rbn));

	/* no sibling left, visit parent */
	return pos->parent;
}