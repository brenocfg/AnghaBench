#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* typname; void* nspname; scalar_t__ remoteid; } ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ LogicalRepTyp ;

/* Variables and functions */
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  LogicalRepRelMapContext ; 
 int /*<<< orphan*/ * LogicalRepTypMap ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 TYPE_1__* hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  logicalrep_relmap_init () ; 
 int /*<<< orphan*/  logicalrep_typmap_free_entry (TYPE_1__*) ; 
 void* pstrdup (void*) ; 

void
logicalrep_typmap_update(LogicalRepTyp *remotetyp)
{
	MemoryContext oldctx;
	LogicalRepTyp *entry;
	bool		found;

	if (LogicalRepTypMap == NULL)
		logicalrep_relmap_init();

	/*
	 * HASH_ENTER returns the existing entry if present or creates a new one.
	 */
	entry = hash_search(LogicalRepTypMap, (void *) &remotetyp->remoteid,
						HASH_ENTER, &found);

	if (found)
		logicalrep_typmap_free_entry(entry);

	/* Make cached copy of the data */
	entry->remoteid = remotetyp->remoteid;
	oldctx = MemoryContextSwitchTo(LogicalRepRelMapContext);
	entry->nspname = pstrdup(remotetyp->nspname);
	entry->typname = pstrdup(remotetyp->typname);
	MemoryContextSwitchTo(oldctx);
}