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
struct rhashtable {int /*<<< orphan*/  mutex; int /*<<< orphan*/  tbl; int /*<<< orphan*/  run_work; } ;
struct rhash_head {unsigned int size; int /*<<< orphan*/  future_tbl; int /*<<< orphan*/  next; } ;
struct bucket_table {unsigned int size; int /*<<< orphan*/  future_tbl; int /*<<< orphan*/  next; } ;

/* Variables and functions */
 int /*<<< orphan*/  bucket_table_free (struct rhash_head*) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rhashtable_free_one (struct rhashtable*,struct rhash_head*,void (*) (void*,void*),void*) ; 
 int /*<<< orphan*/  rht_bucket (struct rhash_head*,unsigned int) ; 
 struct rhash_head* rht_dereference (int /*<<< orphan*/ ,struct rhashtable*) ; 
 int /*<<< orphan*/  rht_is_a_nulls (struct rhash_head*) ; 
 struct rhash_head* rht_ptr_exclusive (int /*<<< orphan*/ ) ; 

void rhashtable_free_and_destroy(struct rhashtable *ht,
				 void (*free_fn)(void *ptr, void *arg),
				 void *arg)
{
	struct bucket_table *tbl, *next_tbl;
	unsigned int i;

	cancel_work_sync(&ht->run_work);

	mutex_lock(&ht->mutex);
	tbl = rht_dereference(ht->tbl, ht);
restart:
	if (free_fn) {
		for (i = 0; i < tbl->size; i++) {
			struct rhash_head *pos, *next;

			cond_resched();
			for (pos = rht_ptr_exclusive(rht_bucket(tbl, i)),
			     next = !rht_is_a_nulls(pos) ?
					rht_dereference(pos->next, ht) : NULL;
			     !rht_is_a_nulls(pos);
			     pos = next,
			     next = !rht_is_a_nulls(pos) ?
					rht_dereference(pos->next, ht) : NULL)
				rhashtable_free_one(ht, pos, free_fn, arg);
		}
	}

	next_tbl = rht_dereference(tbl->future_tbl, ht);
	bucket_table_free(tbl);
	if (next_tbl) {
		tbl = next_tbl;
		goto restart;
	}
	mutex_unlock(&ht->mutex);
}