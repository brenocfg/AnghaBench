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
struct ulist_node {int /*<<< orphan*/  list; int /*<<< orphan*/  rb_node; } ;
struct ulist {scalar_t__ nnodes; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kfree (struct ulist_node*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ulist_rbtree_erase(struct ulist *ulist, struct ulist_node *node)
{
	rb_erase(&node->rb_node, &ulist->root);
	list_del(&node->list);
	kfree(node);
	BUG_ON(ulist->nnodes == 0);
	ulist->nnodes--;
}