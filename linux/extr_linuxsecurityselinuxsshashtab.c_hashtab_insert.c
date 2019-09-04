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
typedef  size_t u32 ;
struct hashtab_node {struct hashtab_node* next; void* datum; void* key; } ;
struct hashtab {scalar_t__ nel; size_t (* hash_value ) (struct hashtab*,void*) ;scalar_t__ (* keycmp ) (struct hashtab*,void*,void*) ;struct hashtab_node** htable; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ HASHTAB_MAX_NODES ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  hashtab_node_cachep ; 
 struct hashtab_node* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t stub1 (struct hashtab*,void*) ; 
 scalar_t__ stub2 (struct hashtab*,void*,void*) ; 
 scalar_t__ stub3 (struct hashtab*,void*,void*) ; 

int hashtab_insert(struct hashtab *h, void *key, void *datum)
{
	u32 hvalue;
	struct hashtab_node *prev, *cur, *newnode;

	cond_resched();

	if (!h || h->nel == HASHTAB_MAX_NODES)
		return -EINVAL;

	hvalue = h->hash_value(h, key);
	prev = NULL;
	cur = h->htable[hvalue];
	while (cur && h->keycmp(h, key, cur->key) > 0) {
		prev = cur;
		cur = cur->next;
	}

	if (cur && (h->keycmp(h, key, cur->key) == 0))
		return -EEXIST;

	newnode = kmem_cache_zalloc(hashtab_node_cachep, GFP_KERNEL);
	if (!newnode)
		return -ENOMEM;
	newnode->key = key;
	newnode->datum = datum;
	if (prev) {
		newnode->next = prev->next;
		prev->next = newnode;
	} else {
		newnode->next = h->htable[hvalue];
		h->htable[hvalue] = newnode;
	}

	h->nel++;
	return 0;
}