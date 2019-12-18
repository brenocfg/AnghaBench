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
struct rhash_lock_head {int dummy; } ;
struct bucket_table {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int rhashtable_rehash_one (struct rhashtable*,struct rhash_lock_head**,unsigned int) ; 
 struct rhash_lock_head** rht_bucket_var (struct bucket_table*,unsigned int) ; 
 struct bucket_table* rht_dereference (int /*<<< orphan*/ ,struct rhashtable*) ; 
 int /*<<< orphan*/  rht_lock (struct bucket_table*,struct rhash_lock_head**) ; 
 int /*<<< orphan*/  rht_unlock (struct bucket_table*,struct rhash_lock_head**) ; 

__attribute__((used)) static int rhashtable_rehash_chain(struct rhashtable *ht,
				    unsigned int old_hash)
{
	struct bucket_table *old_tbl = rht_dereference(ht->tbl, ht);
	struct rhash_lock_head **bkt = rht_bucket_var(old_tbl, old_hash);
	int err;

	if (!bkt)
		return 0;
	rht_lock(old_tbl, bkt);

	while (!(err = rhashtable_rehash_one(ht, bkt, old_hash)))
		;

	if (err == -ENOENT)
		err = 0;
	rht_unlock(old_tbl, bkt);

	return err;
}