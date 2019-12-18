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
struct TYPE_4__ {int /*<<< orphan*/  data; struct avtab_extended_perms* xperms; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
struct avtab_key {int specified; } ;
struct avtab_node {struct avtab_node* next; TYPE_2__ datum; struct avtab_key key; } ;
struct avtab_extended_perms {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; struct avtab_extended_perms* xperms; } ;
struct avtab_datum {TYPE_3__ u; } ;
struct avtab {int /*<<< orphan*/  nel; struct avtab_node** htable; } ;

/* Variables and functions */
 int AVTAB_XPERMS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  avtab_node_cachep ; 
 int /*<<< orphan*/  avtab_xperms_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct avtab_node*) ; 
 void* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct avtab_node*
avtab_insert_node(struct avtab *h, int hvalue,
		  struct avtab_node *prev, struct avtab_node *cur,
		  struct avtab_key *key, struct avtab_datum *datum)
{
	struct avtab_node *newnode;
	struct avtab_extended_perms *xperms;
	newnode = kmem_cache_zalloc(avtab_node_cachep, GFP_KERNEL);
	if (newnode == NULL)
		return NULL;
	newnode->key = *key;

	if (key->specified & AVTAB_XPERMS) {
		xperms = kmem_cache_zalloc(avtab_xperms_cachep, GFP_KERNEL);
		if (xperms == NULL) {
			kmem_cache_free(avtab_node_cachep, newnode);
			return NULL;
		}
		*xperms = *(datum->u.xperms);
		newnode->datum.u.xperms = xperms;
	} else {
		newnode->datum.u.data = datum->u.data;
	}

	if (prev) {
		newnode->next = prev->next;
		prev->next = newnode;
	} else {
		struct avtab_node **n = &h->htable[hvalue];

		newnode->next = *n;
		*n = newnode;
	}

	h->nel++;
	return newnode;
}