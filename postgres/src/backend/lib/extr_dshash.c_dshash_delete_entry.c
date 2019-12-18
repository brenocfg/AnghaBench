#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hash; } ;
typedef  TYPE_2__ dshash_table_item ;
struct TYPE_11__ {int find_locked; int find_exclusively_locked; TYPE_1__* control; } ;
typedef  TYPE_3__ dshash_table ;
struct TYPE_9__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DSHASH_MAGIC ; 
 TYPE_2__* ITEM_FROM_ENTRY (void*) ; 
 int LWLockHeldByMeInMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 size_t PARTITION_FOR_HASH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARTITION_LOCK (TYPE_3__*,size_t) ; 
 int /*<<< orphan*/  delete_item (TYPE_3__*,TYPE_2__*) ; 

void
dshash_delete_entry(dshash_table *hash_table, void *entry)
{
	dshash_table_item *item = ITEM_FROM_ENTRY(entry);
	size_t		partition = PARTITION_FOR_HASH(item->hash);

	Assert(hash_table->control->magic == DSHASH_MAGIC);
	Assert(hash_table->find_locked);
	Assert(hash_table->find_exclusively_locked);
	Assert(LWLockHeldByMeInMode(PARTITION_LOCK(hash_table, partition),
								LW_EXCLUSIVE));

	delete_item(hash_table, item);
	hash_table->find_locked = false;
	hash_table->find_exclusively_locked = false;
	LWLockRelease(PARTITION_LOCK(hash_table, partition));
}