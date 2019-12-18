#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  hash; int /*<<< orphan*/  next; } ;
typedef  TYPE_2__ dshash_table_item ;
struct TYPE_10__ {int /*<<< orphan*/  area; int /*<<< orphan*/ * buckets; TYPE_1__* control; } ;
typedef  TYPE_3__ dshash_table ;
typedef  int /*<<< orphan*/  dsa_pointer ;
struct TYPE_8__ {size_t size_log2; int /*<<< orphan*/  buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t BUCKET_INDEX_FOR_HASH_AND_SIZE (int /*<<< orphan*/ ,size_t) ; 
 size_t DSHASH_NUM_PARTITIONS ; 
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  PARTITION_LOCK (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  dsa_allocate0 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dsa_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_item_into_bucket (TYPE_3__*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
resize(dshash_table *hash_table, size_t new_size_log2)
{
	dsa_pointer old_buckets;
	dsa_pointer new_buckets_shared;
	dsa_pointer *new_buckets;
	size_t		size;
	size_t		new_size = ((size_t) 1) << new_size_log2;
	size_t		i;

	/*
	 * Acquire the locks for all lock partitions.  This is expensive, but we
	 * shouldn't have to do it many times.
	 */
	for (i = 0; i < DSHASH_NUM_PARTITIONS; ++i)
	{
		Assert(!LWLockHeldByMe(PARTITION_LOCK(hash_table, i)));

		LWLockAcquire(PARTITION_LOCK(hash_table, i), LW_EXCLUSIVE);
		if (i == 0 && hash_table->control->size_log2 >= new_size_log2)
		{
			/*
			 * Another backend has already increased the size; we can avoid
			 * obtaining all the locks and return early.
			 */
			LWLockRelease(PARTITION_LOCK(hash_table, 0));
			return;
		}
	}

	Assert(new_size_log2 == hash_table->control->size_log2 + 1);

	/* Allocate the space for the new table. */
	new_buckets_shared = dsa_allocate0(hash_table->area,
									   sizeof(dsa_pointer) * new_size);
	new_buckets = dsa_get_address(hash_table->area, new_buckets_shared);

	/*
	 * We've allocated the new bucket array; all that remains to do now is to
	 * reinsert all items, which amounts to adjusting all the pointers.
	 */
	size = ((size_t) 1) << hash_table->control->size_log2;
	for (i = 0; i < size; ++i)
	{
		dsa_pointer item_pointer = hash_table->buckets[i];

		while (DsaPointerIsValid(item_pointer))
		{
			dshash_table_item *item;
			dsa_pointer next_item_pointer;

			item = dsa_get_address(hash_table->area, item_pointer);
			next_item_pointer = item->next;
			insert_item_into_bucket(hash_table, item_pointer, item,
									&new_buckets[BUCKET_INDEX_FOR_HASH_AND_SIZE(item->hash,
																				new_size_log2)]);
			item_pointer = next_item_pointer;
		}
	}

	/* Swap the hash table into place and free the old one. */
	old_buckets = hash_table->control->buckets;
	hash_table->control->buckets = new_buckets_shared;
	hash_table->control->size_log2 = new_size_log2;
	hash_table->buckets = new_buckets;
	dsa_free(hash_table->area, old_buckets);

	/* Release all the locks. */
	for (i = 0; i < DSHASH_NUM_PARTITIONS; ++i)
		LWLockRelease(PARTITION_LOCK(hash_table, i));
}