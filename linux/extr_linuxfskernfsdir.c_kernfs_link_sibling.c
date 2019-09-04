#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rb_node {int dummy; } ;
struct TYPE_8__ {struct rb_node* rb_right; struct rb_node* rb_left; } ;
struct kernfs_node {TYPE_2__* parent; TYPE_3__ rb; } ;
struct TYPE_9__ {struct rb_node* rb_node; } ;
struct TYPE_6__ {int /*<<< orphan*/  subdirs; TYPE_5__ children; } ;
struct TYPE_7__ {TYPE_1__ dir; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ KERNFS_DIR ; 
 int kernfs_sd_compare (struct kernfs_node*,struct kernfs_node*) ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 int /*<<< orphan*/  rb_insert_color (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  rb_link_node (TYPE_3__*,struct rb_node*,struct rb_node**) ; 
 struct kernfs_node* rb_to_kn (struct rb_node*) ; 

__attribute__((used)) static int kernfs_link_sibling(struct kernfs_node *kn)
{
	struct rb_node **node = &kn->parent->dir.children.rb_node;
	struct rb_node *parent = NULL;

	while (*node) {
		struct kernfs_node *pos;
		int result;

		pos = rb_to_kn(*node);
		parent = *node;
		result = kernfs_sd_compare(kn, pos);
		if (result < 0)
			node = &pos->rb.rb_left;
		else if (result > 0)
			node = &pos->rb.rb_right;
		else
			return -EEXIST;
	}

	/* add new node and rebalance the tree */
	rb_link_node(&kn->rb, parent, node);
	rb_insert_color(&kn->rb, &kn->parent->dir.children);

	/* successfully added, account subdir number */
	if (kernfs_type(kn) == KERNFS_DIR)
		kn->parent->dir.subdirs++;

	return 0;
}