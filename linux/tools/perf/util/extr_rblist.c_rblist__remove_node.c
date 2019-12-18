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
struct rblist {int /*<<< orphan*/  (* node_delete ) (struct rblist*,struct rb_node*) ;int /*<<< orphan*/  nr_entries; int /*<<< orphan*/  entries; } ;
struct rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rb_erase_cached (struct rb_node*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct rblist*,struct rb_node*) ; 

void rblist__remove_node(struct rblist *rblist, struct rb_node *rb_node)
{
	rb_erase_cached(rb_node, &rblist->entries);
	--rblist->nr_entries;
	rblist->node_delete(rblist, rb_node);
}