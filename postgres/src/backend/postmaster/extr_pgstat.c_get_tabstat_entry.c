#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_10__ {scalar_t__ tsa_used; TYPE_3__* tsa_entries; struct TYPE_10__* tsa_next; } ;
typedef  TYPE_1__ TabStatusArray ;
struct TYPE_11__ {TYPE_3__* tsa_entry; } ;
typedef  TYPE_2__ TabStatHashEntry ;
struct TYPE_13__ {int keysize; int entrysize; } ;
struct TYPE_12__ {int t_shared; int /*<<< orphan*/  t_id; } ;
typedef  TYPE_3__ PgStat_TableStatus ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ HASHCTL ;

/* Variables and functions */
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 scalar_t__ MemoryContextAllocZero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ TABSTAT_QUANTUM ; 
 int /*<<< orphan*/  TopMemoryContext ; 
 int /*<<< orphan*/ * hash_create (char*,scalar_t__,TYPE_4__*,int) ; 
 TYPE_2__* hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * pgStatTabHash ; 
 TYPE_1__* pgStatTabList ; 

__attribute__((used)) static PgStat_TableStatus *
get_tabstat_entry(Oid rel_id, bool isshared)
{
	TabStatHashEntry *hash_entry;
	PgStat_TableStatus *entry;
	TabStatusArray *tsa;
	bool		found;

	/*
	 * Create hash table if we don't have it already.
	 */
	if (pgStatTabHash == NULL)
	{
		HASHCTL		ctl;

		memset(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(Oid);
		ctl.entrysize = sizeof(TabStatHashEntry);

		pgStatTabHash = hash_create("pgstat TabStatusArray lookup hash table",
									TABSTAT_QUANTUM,
									&ctl,
									HASH_ELEM | HASH_BLOBS);
	}

	/*
	 * Find an entry or create a new one.
	 */
	hash_entry = hash_search(pgStatTabHash, &rel_id, HASH_ENTER, &found);
	if (!found)
	{
		/* initialize new entry with null pointer */
		hash_entry->tsa_entry = NULL;
	}

	/*
	 * If entry is already valid, we're done.
	 */
	if (hash_entry->tsa_entry)
		return hash_entry->tsa_entry;

	/*
	 * Locate the first pgStatTabList entry with free space, making a new list
	 * entry if needed.  Note that we could get an OOM failure here, but if so
	 * we have left the hashtable and the list in a consistent state.
	 */
	if (pgStatTabList == NULL)
	{
		/* Set up first pgStatTabList entry */
		pgStatTabList = (TabStatusArray *)
			MemoryContextAllocZero(TopMemoryContext,
								   sizeof(TabStatusArray));
	}

	tsa = pgStatTabList;
	while (tsa->tsa_used >= TABSTAT_QUANTUM)
	{
		if (tsa->tsa_next == NULL)
			tsa->tsa_next = (TabStatusArray *)
				MemoryContextAllocZero(TopMemoryContext,
									   sizeof(TabStatusArray));
		tsa = tsa->tsa_next;
	}

	/*
	 * Allocate a PgStat_TableStatus entry within this list entry.  We assume
	 * the entry was already zeroed, either at creation or after last use.
	 */
	entry = &tsa->tsa_entries[tsa->tsa_used++];
	entry->t_id = rel_id;
	entry->t_shared = isshared;

	/*
	 * Now we can fill the entry in pgStatTabHash.
	 */
	hash_entry->tsa_entry = entry;

	return entry;
}