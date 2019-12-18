#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct avtab_node* xperms; } ;
struct TYPE_6__ {TYPE_2__ u; } ;
struct TYPE_4__ {int specified; } ;
struct avtab_node {TYPE_3__ datum; TYPE_1__ key; struct avtab_node* next; } ;
struct avtab {int nslot; scalar_t__ mask; struct avtab_node** htable; } ;

/* Variables and functions */
 int AVTAB_XPERMS ; 
 int /*<<< orphan*/  avtab_node_cachep ; 
 int /*<<< orphan*/  avtab_xperms_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct avtab_node*) ; 
 int /*<<< orphan*/  kvfree (struct avtab_node**) ; 

void avtab_destroy(struct avtab *h)
{
	int i;
	struct avtab_node *cur, *temp;

	if (!h)
		return;

	for (i = 0; i < h->nslot; i++) {
		cur = h->htable[i];
		while (cur) {
			temp = cur;
			cur = cur->next;
			if (temp->key.specified & AVTAB_XPERMS)
				kmem_cache_free(avtab_xperms_cachep,
						temp->datum.u.xperms);
			kmem_cache_free(avtab_node_cachep, temp);
		}
	}
	kvfree(h->htable);
	h->htable = NULL;
	h->nslot = 0;
	h->mask = 0;
}