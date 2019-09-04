#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct TYPE_3__ {struct rb_node* rb_node; } ;
struct TYPE_4__ {TYPE_1__ children; } ;
struct kernfs_node {scalar_t__ hash; void const* ns; int /*<<< orphan*/  rb; TYPE_2__ dir; struct kernfs_node* parent; } ;
typedef  scalar_t__ loff_t ;

/* Variables and functions */
 scalar_t__ INT_MAX ; 
 scalar_t__ kernfs_active (struct kernfs_node*) ; 
 int /*<<< orphan*/  kernfs_put (struct kernfs_node*) ; 
 struct rb_node* rb_next (int /*<<< orphan*/ *) ; 
 struct kernfs_node* rb_to_kn (struct rb_node*) ; 

__attribute__((used)) static struct kernfs_node *kernfs_dir_pos(const void *ns,
	struct kernfs_node *parent, loff_t hash, struct kernfs_node *pos)
{
	if (pos) {
		int valid = kernfs_active(pos) &&
			pos->parent == parent && hash == pos->hash;
		kernfs_put(pos);
		if (!valid)
			pos = NULL;
	}
	if (!pos && (hash > 1) && (hash < INT_MAX)) {
		struct rb_node *node = parent->dir.children.rb_node;
		while (node) {
			pos = rb_to_kn(node);

			if (hash < pos->hash)
				node = node->rb_left;
			else if (hash > pos->hash)
				node = node->rb_right;
			else
				break;
		}
	}
	/* Skip over entries which are dying/dead or in the wrong namespace */
	while (pos && (!kernfs_active(pos) || pos->ns != ns)) {
		struct rb_node *node = rb_next(&pos->rb);
		if (!node)
			pos = NULL;
		else
			pos = rb_to_kn(node);
	}
	return pos;
}