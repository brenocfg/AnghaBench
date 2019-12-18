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
union nested_table {struct rhash_lock_head* bucket; int /*<<< orphan*/  table; } ;
struct rhashtable {int dummy; } ;
struct rhash_lock_head {int dummy; } ;
struct bucket_table {int nest; unsigned int size; int /*<<< orphan*/ * buckets; } ;

/* Variables and functions */
 unsigned int PAGE_SHIFT ; 
 unsigned int ilog2 (int) ; 
 union nested_table* nested_table_alloc (struct rhashtable*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ rcu_dereference_raw (int /*<<< orphan*/ ) ; 

struct rhash_lock_head **rht_bucket_nested_insert(struct rhashtable *ht,
						  struct bucket_table *tbl,
						  unsigned int hash)
{
	const unsigned int shift = PAGE_SHIFT - ilog2(sizeof(void *));
	unsigned int index = hash & ((1 << tbl->nest) - 1);
	unsigned int size = tbl->size >> tbl->nest;
	union nested_table *ntbl;

	ntbl = (union nested_table *)rcu_dereference_raw(tbl->buckets[0]);
	hash >>= tbl->nest;
	ntbl = nested_table_alloc(ht, &ntbl[index].table,
				  size <= (1 << shift));

	while (ntbl && size > (1 << shift)) {
		index = hash & ((1 << shift) - 1);
		size >>= shift;
		hash >>= shift;
		ntbl = nested_table_alloc(ht, &ntbl[index].table,
					  size <= (1 << shift));
	}

	if (!ntbl)
		return NULL;

	return &ntbl[hash].bucket;

}