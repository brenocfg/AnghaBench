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
struct TYPE_3__ {struct rb_node* rb_node; } ;
struct TYPE_4__ {TYPE_1__ rb_root; } ;
struct rblist {int (* node_cmp ) (struct rb_node*,void const*) ;int /*<<< orphan*/  nr_entries; TYPE_2__ entries; struct rb_node* (* node_new ) (struct rblist*,void const*) ;} ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_insert_color_cached (struct rb_node*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  rb_link_node (struct rb_node*,struct rb_node*,struct rb_node**) ; 
 int stub1 (struct rb_node*,void const*) ; 
 struct rb_node* stub2 (struct rblist*,void const*) ; 

__attribute__((used)) static struct rb_node *__rblist__findnew(struct rblist *rblist,
					 const void *entry,
					 bool create)
{
	struct rb_node **p = &rblist->entries.rb_root.rb_node;
	struct rb_node *parent = NULL, *new_node = NULL;
	bool leftmost = true;

	while (*p != NULL) {
		int rc;

		parent = *p;

		rc = rblist->node_cmp(parent, entry);
		if (rc > 0)
			p = &(*p)->rb_left;
		else if (rc < 0) {
			p = &(*p)->rb_right;
			leftmost = false;
		}
		else
			return parent;
	}

	if (create) {
		new_node = rblist->node_new(rblist, entry);
		if (new_node) {
			rb_link_node(new_node, parent, p);
			rb_insert_color_cached(new_node,
					       &rblist->entries, leftmost);
			++rblist->nr_entries;
		}
	}

	return new_node;
}