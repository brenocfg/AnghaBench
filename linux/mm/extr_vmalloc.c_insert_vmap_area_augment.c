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
struct vmap_area {int dummy; } ;
struct rb_root {int dummy; } ;
struct rb_node {int dummy; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  augment_tree_propagate_from (struct vmap_area*) ; 
 struct rb_node** find_va_links (struct vmap_area*,struct rb_root*,struct rb_node*,struct rb_node**) ; 
 int /*<<< orphan*/  link_va (struct vmap_area*,struct rb_root*,struct rb_node*,struct rb_node**,struct list_head*) ; 

__attribute__((used)) static void
insert_vmap_area_augment(struct vmap_area *va,
	struct rb_node *from, struct rb_root *root,
	struct list_head *head)
{
	struct rb_node **link;
	struct rb_node *parent;

	if (from)
		link = find_va_links(va, NULL, from, &parent);
	else
		link = find_va_links(va, root, NULL, &parent);

	link_va(va, root, parent, link, head);
	augment_tree_propagate_from(va);
}