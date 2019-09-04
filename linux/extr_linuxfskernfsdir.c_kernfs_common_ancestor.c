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
struct kernfs_root {int /*<<< orphan*/  kn; } ;
struct kernfs_node {struct kernfs_node* parent; } ;

/* Variables and functions */
 size_t kernfs_depth (int /*<<< orphan*/ ,struct kernfs_node*) ; 
 struct kernfs_root* kernfs_root (struct kernfs_node*) ; 

__attribute__((used)) static struct kernfs_node *kernfs_common_ancestor(struct kernfs_node *a,
						  struct kernfs_node *b)
{
	size_t da, db;
	struct kernfs_root *ra = kernfs_root(a), *rb = kernfs_root(b);

	if (ra != rb)
		return NULL;

	da = kernfs_depth(ra->kn, a);
	db = kernfs_depth(rb->kn, b);

	while (da > db) {
		a = a->parent;
		da--;
	}
	while (db > da) {
		b = b->parent;
		db--;
	}

	/* worst case b and a will be the same at root */
	while (b != a) {
		b = b->parent;
		a = a->parent;
	}

	return a;
}