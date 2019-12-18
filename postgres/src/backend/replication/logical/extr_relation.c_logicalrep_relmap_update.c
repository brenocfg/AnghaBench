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
struct TYPE_8__ {int natts; int /*<<< orphan*/  attkeys; int /*<<< orphan*/  replident; int /*<<< orphan*/ * atttyps; void** attnames; void* relname; void* nspname; scalar_t__ remoteid; } ;
struct TYPE_10__ {TYPE_1__ remoterel; } ;
struct TYPE_9__ {int natts; int /*<<< orphan*/  attkeys; int /*<<< orphan*/  replident; int /*<<< orphan*/ * atttyps; int /*<<< orphan*/ * attnames; int /*<<< orphan*/  relname; int /*<<< orphan*/  nspname; scalar_t__ remoteid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_2__ LogicalRepRelation ;
typedef  TYPE_3__ LogicalRepRelMapEntry ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/ * LogicalRepRelMap ; 
 int /*<<< orphan*/  LogicalRepRelMapContext ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bms_copy (int /*<<< orphan*/ ) ; 
 TYPE_3__* hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  logicalrep_relmap_free_entry (TYPE_3__*) ; 
 int /*<<< orphan*/  logicalrep_relmap_init () ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 void* palloc (int) ; 
 void* pstrdup (int /*<<< orphan*/ ) ; 

void
logicalrep_relmap_update(LogicalRepRelation *remoterel)
{
	MemoryContext oldctx;
	LogicalRepRelMapEntry *entry;
	bool		found;
	int			i;

	if (LogicalRepRelMap == NULL)
		logicalrep_relmap_init();

	/*
	 * HASH_ENTER returns the existing entry if present or creates a new one.
	 */
	entry = hash_search(LogicalRepRelMap, (void *) &remoterel->remoteid,
						HASH_ENTER, &found);

	if (found)
		logicalrep_relmap_free_entry(entry);

	memset(entry, 0, sizeof(LogicalRepRelMapEntry));

	/* Make cached copy of the data */
	oldctx = MemoryContextSwitchTo(LogicalRepRelMapContext);
	entry->remoterel.remoteid = remoterel->remoteid;
	entry->remoterel.nspname = pstrdup(remoterel->nspname);
	entry->remoterel.relname = pstrdup(remoterel->relname);
	entry->remoterel.natts = remoterel->natts;
	entry->remoterel.attnames = palloc(remoterel->natts * sizeof(char *));
	entry->remoterel.atttyps = palloc(remoterel->natts * sizeof(Oid));
	for (i = 0; i < remoterel->natts; i++)
	{
		entry->remoterel.attnames[i] = pstrdup(remoterel->attnames[i]);
		entry->remoterel.atttyps[i] = remoterel->atttyps[i];
	}
	entry->remoterel.replident = remoterel->replident;
	entry->remoterel.attkeys = bms_copy(remoterel->attkeys);
	MemoryContextSwitchTo(oldctx);
}