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
struct rhash_head {int dummy; } ;
struct rhlist_head {struct rhash_head rhead; } ;
struct rhashtable_iter {scalar_t__ skip; struct rhash_head* p; struct rhashtable* ht; struct rhlist_head* list; } ;
struct rhashtable {scalar_t__ rhlist; } ;

/* Variables and functions */
 void* __rhashtable_walk_find_next (struct rhashtable_iter*) ; 
 void* rht_obj (struct rhashtable*,struct rhash_head*) ; 

void *rhashtable_walk_peek(struct rhashtable_iter *iter)
{
	struct rhlist_head *list = iter->list;
	struct rhashtable *ht = iter->ht;
	struct rhash_head *p = iter->p;

	if (p)
		return rht_obj(ht, ht->rhlist ? &list->rhead : p);

	/* No object found in current iter, find next one in the table. */

	if (iter->skip) {
		/* A nonzero skip value points to the next entry in the table
		 * beyond that last one that was found. Decrement skip so
		 * we find the current value. __rhashtable_walk_find_next
		 * will restore the original value of skip assuming that
		 * the table hasn't changed.
		 */
		iter->skip--;
	}

	return __rhashtable_walk_find_next(iter);
}