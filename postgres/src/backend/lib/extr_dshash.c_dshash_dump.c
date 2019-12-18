#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  next; } ;
typedef  TYPE_2__ dshash_table_item ;
struct TYPE_11__ {size_t size_log2; int /*<<< orphan*/  area; int /*<<< orphan*/ * buckets; TYPE_1__* control; int /*<<< orphan*/  find_locked; } ;
typedef  TYPE_3__ dshash_table ;
struct TYPE_12__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_4__ dshash_partition ;
typedef  int /*<<< orphan*/  dsa_pointer ;
struct TYPE_9__ {scalar_t__ magic; TYPE_4__* partitions; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 size_t BUCKET_INDEX_FOR_PARTITION (size_t,size_t) ; 
 scalar_t__ DSHASH_MAGIC ; 
 size_t DSHASH_NUM_PARTITIONS ; 
 scalar_t__ DsaPointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockHeldByMe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_SHARED ; 
 int /*<<< orphan*/  PARTITION_LOCK (TYPE_3__*,size_t) ; 
 TYPE_2__* dsa_get_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ensure_valid_bucket_pointers (TYPE_3__*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  stderr ; 

void
dshash_dump(dshash_table *hash_table)
{
	size_t		i;
	size_t		j;

	Assert(hash_table->control->magic == DSHASH_MAGIC);
	Assert(!hash_table->find_locked);

	for (i = 0; i < DSHASH_NUM_PARTITIONS; ++i)
	{
		Assert(!LWLockHeldByMe(PARTITION_LOCK(hash_table, i)));
		LWLockAcquire(PARTITION_LOCK(hash_table, i), LW_SHARED);
	}

	ensure_valid_bucket_pointers(hash_table);

	fprintf(stderr,
			"hash table size = %zu\n", (size_t) 1 << hash_table->size_log2);
	for (i = 0; i < DSHASH_NUM_PARTITIONS; ++i)
	{
		dshash_partition *partition = &hash_table->control->partitions[i];
		size_t		begin = BUCKET_INDEX_FOR_PARTITION(i, hash_table->size_log2);
		size_t		end = BUCKET_INDEX_FOR_PARTITION(i + 1, hash_table->size_log2);

		fprintf(stderr, "  partition %zu\n", i);
		fprintf(stderr,
				"    active buckets (key count = %zu)\n", partition->count);

		for (j = begin; j < end; ++j)
		{
			size_t		count = 0;
			dsa_pointer bucket = hash_table->buckets[j];

			while (DsaPointerIsValid(bucket))
			{
				dshash_table_item *item;

				item = dsa_get_address(hash_table->area, bucket);

				bucket = item->next;
				++count;
			}
			fprintf(stderr, "      bucket %zu (key count = %zu)\n", j, count);
		}
	}

	for (i = 0; i < DSHASH_NUM_PARTITIONS; ++i)
		LWLockRelease(PARTITION_LOCK(hash_table, i));
}