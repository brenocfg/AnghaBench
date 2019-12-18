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
typedef  scalar_t__ u64 ;
struct ulist_node {scalar_t__ aux; } ;
struct ulist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ulist_rbtree_erase (struct ulist*,struct ulist_node*) ; 
 struct ulist_node* ulist_rbtree_search (struct ulist*,scalar_t__) ; 

int ulist_del(struct ulist *ulist, u64 val, u64 aux)
{
	struct ulist_node *node;

	node = ulist_rbtree_search(ulist, val);
	/* Not found */
	if (!node)
		return 1;

	if (node->aux != aux)
		return 1;

	/* Found and delete */
	ulist_rbtree_erase(ulist, node);
	return 0;
}