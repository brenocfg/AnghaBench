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
typedef  void* u64 ;
struct ulist_node {int /*<<< orphan*/  list; void* aux; void* val; } ;
struct ulist {int /*<<< orphan*/  nnodes; int /*<<< orphan*/  nodes; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int ENOMEM ; 
 struct ulist_node* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ulist_rbtree_insert (struct ulist*,struct ulist_node*) ; 
 struct ulist_node* ulist_rbtree_search (struct ulist*,void*) ; 

int ulist_add_merge(struct ulist *ulist, u64 val, u64 aux,
		    u64 *old_aux, gfp_t gfp_mask)
{
	int ret;
	struct ulist_node *node;

	node = ulist_rbtree_search(ulist, val);
	if (node) {
		if (old_aux)
			*old_aux = node->aux;
		return 0;
	}
	node = kmalloc(sizeof(*node), gfp_mask);
	if (!node)
		return -ENOMEM;

	node->val = val;
	node->aux = aux;

	ret = ulist_rbtree_insert(ulist, node);
	ASSERT(!ret);
	list_add_tail(&node->list, &ulist->nodes);
	ulist->nnodes++;

	return 1;
}