#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
typedef  size_t int32 ;
typedef  int /*<<< orphan*/  dsm_segment ;
typedef  int /*<<< orphan*/  dshash_table ;
typedef  void* dsa_pointer ;
typedef  int /*<<< orphan*/  dsa_area ;
typedef  TYPE_4__* TupleDesc ;
struct TYPE_17__ {TYPE_4__* local_tupdesc; } ;
struct TYPE_23__ {int shared; TYPE_1__ u; } ;
struct TYPE_22__ {int /*<<< orphan*/  next_typmod; void* typmod_table_handle; void* record_table_handle; } ;
struct TYPE_18__ {void* shared_tupdesc; } ;
struct TYPE_19__ {int shared; TYPE_2__ u; } ;
struct TYPE_21__ {TYPE_3__ key; void* shared_tupdesc; TYPE_7__ typmod; } ;
struct TYPE_20__ {TYPE_7__ tdtypmod; } ;
struct TYPE_16__ {TYPE_6__* shared_typmod_registry; int /*<<< orphan*/ * shared_typmod_table; int /*<<< orphan*/ * shared_record_table; } ;
typedef  TYPE_5__ SharedTypmodTableEntry ;
typedef  TYPE_6__ SharedRecordTypmodRegistry ;
typedef  TYPE_7__ SharedRecordTableKey ;
typedef  TYPE_5__ SharedRecordTableEntry ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 TYPE_15__* CurrentSession ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IsParallelWorker () ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 size_t NextRecordTypmod ; 
 TYPE_4__** RecordCacheArray ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ * dshash_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__* dshash_find_or_insert (int /*<<< orphan*/ *,TYPE_7__*,int*) ; 
 void* dshash_get_hash_table_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dshash_release_lock (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  on_dsm_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_atomic_init_u32 (int /*<<< orphan*/ *,size_t) ; 
 void* share_tupledesc (int /*<<< orphan*/ *,TYPE_4__*,size_t) ; 
 int /*<<< orphan*/  shared_record_typmod_registry_detach ; 
 int /*<<< orphan*/  srtr_record_table_params ; 
 int /*<<< orphan*/  srtr_typmod_table_params ; 

void
SharedRecordTypmodRegistryInit(SharedRecordTypmodRegistry *registry,
							   dsm_segment *segment,
							   dsa_area *area)
{
	MemoryContext old_context;
	dshash_table *record_table;
	dshash_table *typmod_table;
	int32		typmod;

	Assert(!IsParallelWorker());

	/* We can't already be attached to a shared registry. */
	Assert(CurrentSession->shared_typmod_registry == NULL);
	Assert(CurrentSession->shared_record_table == NULL);
	Assert(CurrentSession->shared_typmod_table == NULL);

	old_context = MemoryContextSwitchTo(TopMemoryContext);

	/* Create the hash table of tuple descriptors indexed by themselves. */
	record_table = dshash_create(area, &srtr_record_table_params, area);

	/* Create the hash table of tuple descriptors indexed by typmod. */
	typmod_table = dshash_create(area, &srtr_typmod_table_params, NULL);

	MemoryContextSwitchTo(old_context);

	/* Initialize the SharedRecordTypmodRegistry. */
	registry->record_table_handle = dshash_get_hash_table_handle(record_table);
	registry->typmod_table_handle = dshash_get_hash_table_handle(typmod_table);
	pg_atomic_init_u32(&registry->next_typmod, NextRecordTypmod);

	/*
	 * Copy all entries from this backend's private registry into the shared
	 * registry.
	 */
	for (typmod = 0; typmod < NextRecordTypmod; ++typmod)
	{
		SharedTypmodTableEntry *typmod_table_entry;
		SharedRecordTableEntry *record_table_entry;
		SharedRecordTableKey record_table_key;
		dsa_pointer shared_dp;
		TupleDesc	tupdesc;
		bool		found;

		tupdesc = RecordCacheArray[typmod];
		if (tupdesc == NULL)
			continue;

		/* Copy the TupleDesc into shared memory. */
		shared_dp = share_tupledesc(area, tupdesc, typmod);

		/* Insert into the typmod table. */
		typmod_table_entry = dshash_find_or_insert(typmod_table,
												   &tupdesc->tdtypmod,
												   &found);
		if (found)
			elog(ERROR, "cannot create duplicate shared record typmod");
		typmod_table_entry->typmod = tupdesc->tdtypmod;
		typmod_table_entry->shared_tupdesc = shared_dp;
		dshash_release_lock(typmod_table, typmod_table_entry);

		/* Insert into the record table. */
		record_table_key.shared = false;
		record_table_key.u.local_tupdesc = tupdesc;
		record_table_entry = dshash_find_or_insert(record_table,
												   &record_table_key,
												   &found);
		if (!found)
		{
			record_table_entry->key.shared = true;
			record_table_entry->key.u.shared_tupdesc = shared_dp;
		}
		dshash_release_lock(record_table, record_table_entry);
	}

	/*
	 * Set up the global state that will tell assign_record_type_typmod and
	 * lookup_rowtype_tupdesc_internal about the shared registry.
	 */
	CurrentSession->shared_record_table = record_table;
	CurrentSession->shared_typmod_table = typmod_table;
	CurrentSession->shared_typmod_registry = registry;

	/*
	 * We install a detach hook in the leader, but only to handle cleanup on
	 * failure during GetSessionDsmHandle().  Once GetSessionDsmHandle() pins
	 * the memory, the leader process will use a shared registry until it
	 * exits.
	 */
	on_dsm_detach(segment, shared_record_typmod_registry_detach, (Datum) 0);
}