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
struct btrfs_stripe_hash_table {struct btrfs_stripe_hash* table; int /*<<< orphan*/  stripe_cache; int /*<<< orphan*/  cache_lock; } ;
struct btrfs_stripe_hash {int /*<<< orphan*/  lock; int /*<<< orphan*/  hash_list; } ;
struct btrfs_fs_info {scalar_t__ stripe_hash_table; } ;

/* Variables and functions */
 int BTRFS_STRIPE_HASH_TABLE_BITS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct btrfs_stripe_hash_table* cmpxchg (scalar_t__*,int /*<<< orphan*/ *,struct btrfs_stripe_hash_table*) ; 
 int /*<<< orphan*/  kvfree (struct btrfs_stripe_hash_table*) ; 
 struct btrfs_stripe_hash_table* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int btrfs_alloc_stripe_hash_table(struct btrfs_fs_info *info)
{
	struct btrfs_stripe_hash_table *table;
	struct btrfs_stripe_hash_table *x;
	struct btrfs_stripe_hash *cur;
	struct btrfs_stripe_hash *h;
	int num_entries = 1 << BTRFS_STRIPE_HASH_TABLE_BITS;
	int i;
	int table_size;

	if (info->stripe_hash_table)
		return 0;

	/*
	 * The table is large, starting with order 4 and can go as high as
	 * order 7 in case lock debugging is turned on.
	 *
	 * Try harder to allocate and fallback to vmalloc to lower the chance
	 * of a failing mount.
	 */
	table_size = sizeof(*table) + sizeof(*h) * num_entries;
	table = kvzalloc(table_size, GFP_KERNEL);
	if (!table)
		return -ENOMEM;

	spin_lock_init(&table->cache_lock);
	INIT_LIST_HEAD(&table->stripe_cache);

	h = table->table;

	for (i = 0; i < num_entries; i++) {
		cur = h + i;
		INIT_LIST_HEAD(&cur->hash_list);
		spin_lock_init(&cur->lock);
	}

	x = cmpxchg(&info->stripe_hash_table, NULL, table);
	if (x)
		kvfree(x);
	return 0;
}