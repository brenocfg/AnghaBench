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
struct rhashtable {int /*<<< orphan*/  run_work; int /*<<< orphan*/  tbl; } ;
struct bucket_table {unsigned int size; int /*<<< orphan*/  future_tbl; } ;

/* Variables and functions */
 int EBUSY ; 
 int EEXIST ; 
 int ENOMEM ; 
 int GFP_ATOMIC ; 
 int __GFP_NOWARN ; 
 struct bucket_table* bucket_table_alloc (struct rhashtable*,unsigned int,int) ; 
 int /*<<< orphan*/  bucket_table_free (struct bucket_table*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_access_pointer (int /*<<< orphan*/ ) ; 
 int rhashtable_rehash_attach (struct rhashtable*,struct bucket_table*,struct bucket_table*) ; 
 struct bucket_table* rht_dereference_rcu (int /*<<< orphan*/ ,struct rhashtable*) ; 
 scalar_t__ rht_grow_above_75 (struct rhashtable*,struct bucket_table*) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rhashtable_insert_rehash(struct rhashtable *ht,
				    struct bucket_table *tbl)
{
	struct bucket_table *old_tbl;
	struct bucket_table *new_tbl;
	unsigned int size;
	int err;

	old_tbl = rht_dereference_rcu(ht->tbl, ht);

	size = tbl->size;

	err = -EBUSY;

	if (rht_grow_above_75(ht, tbl))
		size *= 2;
	/* Do not schedule more than one rehash */
	else if (old_tbl != tbl)
		goto fail;

	err = -ENOMEM;

	new_tbl = bucket_table_alloc(ht, size, GFP_ATOMIC | __GFP_NOWARN);
	if (new_tbl == NULL)
		goto fail;

	err = rhashtable_rehash_attach(ht, tbl, new_tbl);
	if (err) {
		bucket_table_free(new_tbl);
		if (err == -EEXIST)
			err = 0;
	} else
		schedule_work(&ht->run_work);

	return err;

fail:
	/* Do not fail the insert if someone else did a rehash. */
	if (likely(rcu_access_pointer(tbl->future_tbl)))
		return 0;

	/* Schedule async rehash to retry allocation in process context. */
	if (err == -ENOMEM)
		schedule_work(&ht->run_work);

	return err;
}