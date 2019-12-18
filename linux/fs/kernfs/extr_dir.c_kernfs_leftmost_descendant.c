#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rb_node {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  children; } ;
struct kernfs_node {TYPE_1__ dir; } ;

/* Variables and functions */
 scalar_t__ KERNFS_DIR ; 
 scalar_t__ kernfs_type (struct kernfs_node*) ; 
 struct rb_node* rb_first (int /*<<< orphan*/ *) ; 
 struct kernfs_node* rb_to_kn (struct rb_node*) ; 

__attribute__((used)) static struct kernfs_node *kernfs_leftmost_descendant(struct kernfs_node *pos)
{
	struct kernfs_node *last;

	while (true) {
		struct rb_node *rbn;

		last = pos;

		if (kernfs_type(pos) != KERNFS_DIR)
			break;

		rbn = rb_first(&pos->dir.children);
		if (!rbn)
			break;

		pos = rb_to_kn(rbn);
	}

	return last;
}