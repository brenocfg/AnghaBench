#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dshash_table_handle ;
struct TYPE_5__ {int find_locked; int find_exclusively_locked; scalar_t__ size_log2; int /*<<< orphan*/ * buckets; TYPE_4__* control; void* arg; int /*<<< orphan*/  params; int /*<<< orphan*/ * area; } ;
typedef  TYPE_1__ dshash_table ;
typedef  int /*<<< orphan*/  dshash_parameters ;
typedef  int /*<<< orphan*/  dsa_pointer ;
typedef  int /*<<< orphan*/  dsa_area ;
struct TYPE_6__ {scalar_t__ magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ DSHASH_MAGIC ; 
 TYPE_4__* dsa_get_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* palloc (int) ; 

dshash_table *
dshash_attach(dsa_area *area, const dshash_parameters *params,
			  dshash_table_handle handle, void *arg)
{
	dshash_table *hash_table;
	dsa_pointer control;

	/* Allocate the backend-local object representing the hash table. */
	hash_table = palloc(sizeof(dshash_table));

	/* Find the control object in shared memory. */
	control = handle;

	/* Set up the local hash table struct. */
	hash_table->area = area;
	hash_table->params = *params;
	hash_table->arg = arg;
	hash_table->control = dsa_get_address(area, control);
	hash_table->find_locked = false;
	hash_table->find_exclusively_locked = false;
	Assert(hash_table->control->magic == DSHASH_MAGIC);

	/*
	 * These will later be set to the correct values by
	 * ensure_valid_bucket_pointers(), at which time we'll be holding a
	 * partition lock for interlocking against concurrent resizing.
	 */
	hash_table->buckets = NULL;
	hash_table->size_log2 = 0;

	return hash_table;
}