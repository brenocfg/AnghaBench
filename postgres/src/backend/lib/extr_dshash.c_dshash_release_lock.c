#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_2__ dshash_table_item ;
struct TYPE_9__ {int find_locked; int find_exclusively_locked; TYPE_1__* control; } ;
typedef  TYPE_3__ dshash_table ;
struct TYPE_7__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DSHASH_MAGIC ; 
 TYPE_2__* ITEM_FROM_ENTRY (void*) ; 
 int LWLockHeldByMeInMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 int /*<<< orphan*/  LW_SHARED ; 
 size_t PARTITION_FOR_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARTITION_LOCK (TYPE_3__*,size_t) ; 

void
dshash_release_lock(dshash_table *hash_table, void *entry)
{
	dshash_table_item *item = ITEM_FROM_ENTRY(entry);
	size_t		partition_index = PARTITION_FOR_HASH(item->hash);

	Assert(hash_table->control->magic == DSHASH_MAGIC);
	Assert(hash_table->find_locked);
	Assert(LWLockHeldByMeInMode(PARTITION_LOCK(hash_table, partition_index),
								hash_table->find_exclusively_locked
								? LW_EXCLUSIVE : LW_SHARED));

	hash_table->find_locked = false;
	hash_table->find_exclusively_locked = false;
	LWLockRelease(PARTITION_LOCK(hash_table, partition_index));
}