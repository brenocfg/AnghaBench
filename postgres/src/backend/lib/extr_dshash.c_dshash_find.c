#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dshash_table_item ;
struct TYPE_10__ {int find_locked; int find_exclusively_locked; TYPE_1__* control; } ;
typedef  TYPE_2__ dshash_table ;
typedef  int /*<<< orphan*/  dshash_hash ;
struct TYPE_9__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BUCKET_FOR_HASH (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ DSHASH_MAGIC ; 
 void* ENTRY_FROM_ITEM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LW_SHARED ; 
 size_t PARTITION_FOR_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARTITION_LOCK (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  ensure_valid_bucket_pointers (TYPE_2__*) ; 
 int /*<<< orphan*/ * find_in_bucket (TYPE_2__*,void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hash_key (TYPE_2__*,void const*) ; 

void *
dshash_find(dshash_table *hash_table, const void *key, bool exclusive)
{
	dshash_hash hash;
	size_t		partition;
	dshash_table_item *item;

	hash = hash_key(hash_table, key);
	partition = PARTITION_FOR_HASH(hash);

	Assert(hash_table->control->magic == DSHASH_MAGIC);
	Assert(!hash_table->find_locked);

	LWLockAcquire(PARTITION_LOCK(hash_table, partition),
				  exclusive ? LW_EXCLUSIVE : LW_SHARED);
	ensure_valid_bucket_pointers(hash_table);

	/* Search the active bucket. */
	item = find_in_bucket(hash_table, key, BUCKET_FOR_HASH(hash_table, hash));

	if (!item)
	{
		/* Not found. */
		LWLockRelease(PARTITION_LOCK(hash_table, partition));
		return NULL;
	}
	else
	{
		/* The caller will free the lock by calling dshash_release_lock. */
		hash_table->find_locked = true;
		hash_table->find_exclusively_locked = exclusive;
		return ENTRY_FROM_ITEM(item);
	}
}