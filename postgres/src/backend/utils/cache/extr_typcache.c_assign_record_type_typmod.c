#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
typedef  TYPE_1__* TupleDesc ;
struct TYPE_14__ {int keysize; int entrysize; int /*<<< orphan*/  match; int /*<<< orphan*/  hash; } ;
struct TYPE_13__ {TYPE_1__* tupdesc; } ;
struct TYPE_12__ {scalar_t__ tdtypeid; size_t tdtypmod; int tdrefcount; } ;
typedef  TYPE_2__ RecordCacheEntry ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_3__ HASHCTL ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 TYPE_1__* CreateTupleDescCopy (TYPE_1__*) ; 
 int HASH_COMPARE ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int HASH_FUNCTION ; 
 int /*<<< orphan*/  MemSet (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NextRecordTypmod ; 
 scalar_t__ RECORDOID ; 
 TYPE_1__** RecordCacheArray ; 
 int /*<<< orphan*/ * RecordCacheHash ; 
 scalar_t__* RecordIdentifierArray ; 
 int /*<<< orphan*/  ensure_record_cache_typmod_slot_exists (size_t) ; 
 TYPE_1__* find_or_make_matching_shared_tupledesc (TYPE_1__*) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_3__*,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  record_type_typmod_compare ; 
 int /*<<< orphan*/  record_type_typmod_hash ; 
 scalar_t__ tupledesc_id_counter ; 

void
assign_record_type_typmod(TupleDesc tupDesc)
{
	RecordCacheEntry *recentry;
	TupleDesc	entDesc;
	bool		found;
	MemoryContext oldcxt;

	Assert(tupDesc->tdtypeid == RECORDOID);

	if (RecordCacheHash == NULL)
	{
		/* First time through: initialize the hash table */
		HASHCTL		ctl;

		MemSet(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(TupleDesc);	/* just the pointer */
		ctl.entrysize = sizeof(RecordCacheEntry);
		ctl.hash = record_type_typmod_hash;
		ctl.match = record_type_typmod_compare;
		RecordCacheHash = hash_create("Record information cache", 64,
									  &ctl,
									  HASH_ELEM | HASH_FUNCTION | HASH_COMPARE);

		/* Also make sure CacheMemoryContext exists */
		if (!CacheMemoryContext)
			CreateCacheMemoryContext();
	}

	/* Find or create a hashtable entry for this tuple descriptor */
	recentry = (RecordCacheEntry *) hash_search(RecordCacheHash,
												(void *) &tupDesc,
												HASH_ENTER, &found);
	if (found && recentry->tupdesc != NULL)
	{
		tupDesc->tdtypmod = recentry->tupdesc->tdtypmod;
		return;
	}

	/* Not present, so need to manufacture an entry */
	recentry->tupdesc = NULL;
	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);

	/* Look in the SharedRecordTypmodRegistry, if attached */
	entDesc = find_or_make_matching_shared_tupledesc(tupDesc);
	if (entDesc == NULL)
	{
		/* Reference-counted local cache only. */
		entDesc = CreateTupleDescCopy(tupDesc);
		entDesc->tdrefcount = 1;
		entDesc->tdtypmod = NextRecordTypmod++;
	}
	ensure_record_cache_typmod_slot_exists(entDesc->tdtypmod);
	RecordCacheArray[entDesc->tdtypmod] = entDesc;
	recentry->tupdesc = entDesc;

	/* Assign a unique tupdesc identifier, too. */
	RecordIdentifierArray[entDesc->tdtypmod] = ++tupledesc_id_counter;

	/* Update the caller's tuple descriptor. */
	tupDesc->tdtypmod = entDesc->tdtypmod;

	MemoryContextSwitchTo(oldcxt);
}