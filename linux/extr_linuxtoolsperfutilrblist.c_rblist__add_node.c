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
struct TYPE_2__ {struct rb_node* rb_node; } ;
struct rblist {int (* node_cmp ) (struct rb_node*,void const*) ;int /*<<< orphan*/  nr_entries; TYPE_1__ entries; struct rb_node* (* node_new ) (struct rblist*,void const*) ;} ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  rb_insert_color (struct rb_node*,TYPE_1__*) ; 
 int /*<<< orphan*/  rb_link_node (struct rb_node*,struct rb_node*,struct rb_node**) ; 
 int stub1 (struct rb_node*,void const*) ; 
 struct rb_node* stub2 (struct rblist*,void const*) ; 

int rblist__add_node(struct rblist *rblist, const void *new_entry)
{
	struct rb_node **p = &rblist->entries.rb_node;
	struct rb_node *parent = NULL, *new_node;

	while (*p != NULL) {
		int rc;

		parent = *p;

		rc = rblist->node_cmp(parent, new_entry);
		if (rc > 0)
			p = &(*p)->rb_left;
		else if (rc < 0)
			p = &(*p)->rb_right;
		else
			return -EEXIST;
	}

	new_node = rblist->node_new(rblist, new_entry);
	if (new_node == NULL)
		return -ENOMEM;

	rb_link_node(new_node, parent, p);
	rb_insert_color(new_node, &rblist->entries);
	++rblist->nr_entries;

	return 0;
}