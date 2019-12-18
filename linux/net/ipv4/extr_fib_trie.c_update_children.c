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
struct key_vector {int dummy; } ;

/* Variables and functions */
 unsigned long child_length (struct key_vector*) ; 
 struct key_vector* get_child (struct key_vector*,unsigned long) ; 
 struct key_vector* node_parent (struct key_vector*) ; 
 int /*<<< orphan*/  node_set_parent (struct key_vector*,struct key_vector*) ; 

__attribute__((used)) static void update_children(struct key_vector *tn)
{
	unsigned long i;

	/* update all of the child parent pointers */
	for (i = child_length(tn); i;) {
		struct key_vector *inode = get_child(tn, --i);

		if (!inode)
			continue;

		/* Either update the children of a tnode that
		 * already belongs to us or update the child
		 * to point to ourselves.
		 */
		if (node_parent(inode) == tn)
			update_children(inode);
		else
			node_set_parent(inode, tn);
	}
}