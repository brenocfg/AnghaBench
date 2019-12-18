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
struct hashtab_node {void* datum; int /*<<< orphan*/  key; struct hashtab_node* next; } ;
struct hashtab {size_t (* hash_value ) (struct hashtab*,void const*) ;scalar_t__ (* keycmp ) (struct hashtab*,void const*,int /*<<< orphan*/ ) ;struct hashtab_node** htable; } ;

/* Variables and functions */
 size_t stub1 (struct hashtab*,void const*) ; 
 scalar_t__ stub2 (struct hashtab*,void const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub3 (struct hashtab*,void const*,int /*<<< orphan*/ ) ; 

void *hashtab_search(struct hashtab *h, const void *key)
{
	u32 hvalue;
	struct hashtab_node *cur;

	if (!h)
		return NULL;

	hvalue = h->hash_value(h, key);
	cur = h->htable[hvalue];
	while (cur && h->keycmp(h, key, cur->key) > 0)
		cur = cur->next;

	if (!cur || (h->keycmp(h, key, cur->key) != 0))
		return NULL;

	return cur->datum;
}