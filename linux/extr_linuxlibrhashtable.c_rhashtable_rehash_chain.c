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
struct rhashtable {int /*<<< orphan*/  tbl; } ;
struct bucket_table {int /*<<< orphan*/  rehash; } ;
typedef  int /*<<< orphan*/  spinlock_t ;

/* Variables and functions */
 int ENOENT ; 
 int rhashtable_rehash_one (struct rhashtable*,unsigned int) ; 
 int /*<<< orphan*/ * rht_bucket_lock (struct bucket_table*,unsigned int) ; 
 struct bucket_table* rht_dereference (int /*<<< orphan*/ ,struct rhashtable*) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rhashtable_rehash_chain(struct rhashtable *ht,
				    unsigned int old_hash)
{
	struct bucket_table *old_tbl = rht_dereference(ht->tbl, ht);
	spinlock_t *old_bucket_lock;
	int err;

	old_bucket_lock = rht_bucket_lock(old_tbl, old_hash);

	spin_lock_bh(old_bucket_lock);
	while (!(err = rhashtable_rehash_one(ht, old_hash)))
		;

	if (err == -ENOENT) {
		old_tbl->rehash++;
		err = 0;
	}
	spin_unlock_bh(old_bucket_lock);

	return err;
}