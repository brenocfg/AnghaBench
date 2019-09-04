#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct btrfs_stripe_hash_table {int cache_size; struct btrfs_stripe_hash* table; } ;
struct btrfs_stripe_hash {int /*<<< orphan*/  lock; } ;
struct btrfs_raid_bio {int /*<<< orphan*/  bio_list_lock; int /*<<< orphan*/  plug_list; int /*<<< orphan*/  refs; int /*<<< orphan*/  hash_list; int /*<<< orphan*/  bio_list; int /*<<< orphan*/  stripe_cache; int /*<<< orphan*/  flags; TYPE_1__* fs_info; } ;
struct TYPE_2__ {struct btrfs_stripe_hash_table* stripe_hash_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  RBIO_CACHE_BIT ; 
 int /*<<< orphan*/  __free_raid_bio (struct btrfs_raid_bio*) ; 
 scalar_t__ bio_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int rbio_bucket (struct btrfs_raid_bio*) ; 
 int /*<<< orphan*/  refcount_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __remove_rbio_from_cache(struct btrfs_raid_bio *rbio)
{
	int bucket = rbio_bucket(rbio);
	struct btrfs_stripe_hash_table *table;
	struct btrfs_stripe_hash *h;
	int freeit = 0;

	/*
	 * check the bit again under the hash table lock.
	 */
	if (!test_bit(RBIO_CACHE_BIT, &rbio->flags))
		return;

	table = rbio->fs_info->stripe_hash_table;
	h = table->table + bucket;

	/* hold the lock for the bucket because we may be
	 * removing it from the hash table
	 */
	spin_lock(&h->lock);

	/*
	 * hold the lock for the bio list because we need
	 * to make sure the bio list is empty
	 */
	spin_lock(&rbio->bio_list_lock);

	if (test_and_clear_bit(RBIO_CACHE_BIT, &rbio->flags)) {
		list_del_init(&rbio->stripe_cache);
		table->cache_size -= 1;
		freeit = 1;

		/* if the bio list isn't empty, this rbio is
		 * still involved in an IO.  We take it out
		 * of the cache list, and drop the ref that
		 * was held for the list.
		 *
		 * If the bio_list was empty, we also remove
		 * the rbio from the hash_table, and drop
		 * the corresponding ref
		 */
		if (bio_list_empty(&rbio->bio_list)) {
			if (!list_empty(&rbio->hash_list)) {
				list_del_init(&rbio->hash_list);
				refcount_dec(&rbio->refs);
				BUG_ON(!list_empty(&rbio->plug_list));
			}
		}
	}

	spin_unlock(&rbio->bio_list_lock);
	spin_unlock(&h->lock);

	if (freeit)
		__free_raid_bio(rbio);
}