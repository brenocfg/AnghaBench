#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_14__ {int /*<<< orphan*/  triggerlist; } ;
struct TYPE_13__ {scalar_t__ enabled; int /*<<< orphan*/  ntags; int /*<<< orphan*/  tag; int /*<<< orphan*/  fnoid; } ;
struct TYPE_12__ {scalar_t__ evtenabled; int /*<<< orphan*/  evtfoid; int /*<<< orphan*/  evtevent; } ;
struct TYPE_11__ {int keysize; int entrysize; int /*<<< orphan*/ * hcxt; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__ HASHCTL ;
typedef  TYPE_2__* Form_pg_event_trigger ;
typedef  int /*<<< orphan*/  EventTriggerEvent ;
typedef  TYPE_3__ EventTriggerCacheItem ;
typedef  TYPE_4__ EventTriggerCacheEntry ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Anum_pg_event_trigger_evttags ; 
 int /*<<< orphan*/ * CacheMemoryContext ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 int /*<<< orphan*/  DecodeTextArrayToCString (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ETCS_REBUILD_STARTED ; 
 scalar_t__ ETCS_VALID ; 
 int /*<<< orphan*/  EVENTTRIGGEROID ; 
 int /*<<< orphan*/  EVT_DDLCommandEnd ; 
 int /*<<< orphan*/  EVT_DDLCommandStart ; 
 int /*<<< orphan*/  EVT_SQLDrop ; 
 int /*<<< orphan*/  EVT_TableRewrite ; 
 int /*<<< orphan*/ * EventTriggerCache ; 
 int /*<<< orphan*/ * EventTriggerCacheContext ; 
 scalar_t__ EventTriggerCacheState ; 
 int /*<<< orphan*/  EventTriggerNameIndexId ; 
 int /*<<< orphan*/  EventTriggerRelationId ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_CONTEXT ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateEventCacheCallback ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextResetAndDeleteChildren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 scalar_t__ TRIGGER_DISABLED ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_1__*,int) ; 
 TYPE_4__* hash_search (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  heap_getattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  index_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lappend (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  list_make1 (TYPE_3__*) ; 
 TYPE_3__* palloc0 (int) ; 
 int /*<<< orphan*/  pg_qsort_strcmp ; 
 int /*<<< orphan*/  qsort (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  systable_beginscan_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan_ordered (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext_ordered (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
BuildEventTriggerCache(void)
{
	HASHCTL		ctl;
	HTAB	   *cache;
	MemoryContext oldcontext;
	Relation	rel;
	Relation	irel;
	SysScanDesc scan;

	if (EventTriggerCacheContext != NULL)
	{
		/*
		 * Free up any memory already allocated in EventTriggerCacheContext.
		 * This can happen either because a previous rebuild failed, or
		 * because an invalidation happened before the rebuild was complete.
		 */
		MemoryContextResetAndDeleteChildren(EventTriggerCacheContext);
	}
	else
	{
		/*
		 * This is our first time attempting to build the cache, so we need to
		 * set up the memory context and register a syscache callback to
		 * capture future invalidation events.
		 */
		if (CacheMemoryContext == NULL)
			CreateCacheMemoryContext();
		EventTriggerCacheContext =
			AllocSetContextCreate(CacheMemoryContext,
								  "EventTriggerCache",
								  ALLOCSET_DEFAULT_SIZES);
		CacheRegisterSyscacheCallback(EVENTTRIGGEROID,
									  InvalidateEventCacheCallback,
									  (Datum) 0);
	}

	/* Switch to correct memory context. */
	oldcontext = MemoryContextSwitchTo(EventTriggerCacheContext);

	/* Prevent the memory context from being nuked while we're rebuilding. */
	EventTriggerCacheState = ETCS_REBUILD_STARTED;

	/* Create new hash table. */
	MemSet(&ctl, 0, sizeof(ctl));
	ctl.keysize = sizeof(EventTriggerEvent);
	ctl.entrysize = sizeof(EventTriggerCacheEntry);
	ctl.hcxt = EventTriggerCacheContext;
	cache = hash_create("Event Trigger Cache", 32, &ctl,
						HASH_ELEM | HASH_BLOBS | HASH_CONTEXT);

	/*
	 * Prepare to scan pg_event_trigger in name order.
	 */
	rel = relation_open(EventTriggerRelationId, AccessShareLock);
	irel = index_open(EventTriggerNameIndexId, AccessShareLock);
	scan = systable_beginscan_ordered(rel, irel, NULL, 0, NULL);

	/*
	 * Build a cache item for each pg_event_trigger tuple, and append each one
	 * to the appropriate cache entry.
	 */
	for (;;)
	{
		HeapTuple	tup;
		Form_pg_event_trigger form;
		char	   *evtevent;
		EventTriggerEvent event;
		EventTriggerCacheItem *item;
		Datum		evttags;
		bool		evttags_isnull;
		EventTriggerCacheEntry *entry;
		bool		found;

		/* Get next tuple. */
		tup = systable_getnext_ordered(scan, ForwardScanDirection);
		if (!HeapTupleIsValid(tup))
			break;

		/* Skip trigger if disabled. */
		form = (Form_pg_event_trigger) GETSTRUCT(tup);
		if (form->evtenabled == TRIGGER_DISABLED)
			continue;

		/* Decode event name. */
		evtevent = NameStr(form->evtevent);
		if (strcmp(evtevent, "ddl_command_start") == 0)
			event = EVT_DDLCommandStart;
		else if (strcmp(evtevent, "ddl_command_end") == 0)
			event = EVT_DDLCommandEnd;
		else if (strcmp(evtevent, "sql_drop") == 0)
			event = EVT_SQLDrop;
		else if (strcmp(evtevent, "table_rewrite") == 0)
			event = EVT_TableRewrite;
		else
			continue;

		/* Allocate new cache item. */
		item = palloc0(sizeof(EventTriggerCacheItem));
		item->fnoid = form->evtfoid;
		item->enabled = form->evtenabled;

		/* Decode and sort tags array. */
		evttags = heap_getattr(tup, Anum_pg_event_trigger_evttags,
							   RelationGetDescr(rel), &evttags_isnull);
		if (!evttags_isnull)
		{
			item->ntags = DecodeTextArrayToCString(evttags, &item->tag);
			qsort(item->tag, item->ntags, sizeof(char *), pg_qsort_strcmp);
		}

		/* Add to cache entry. */
		entry = hash_search(cache, &event, HASH_ENTER, &found);
		if (found)
			entry->triggerlist = lappend(entry->triggerlist, item);
		else
			entry->triggerlist = list_make1(item);
	}

	/* Done with pg_event_trigger scan. */
	systable_endscan_ordered(scan);
	index_close(irel, AccessShareLock);
	relation_close(rel, AccessShareLock);

	/* Restore previous memory context. */
	MemoryContextSwitchTo(oldcontext);

	/* Install new cache. */
	EventTriggerCache = cache;

	/*
	 * If the cache has been invalidated since we entered this routine, we
	 * still use and return the cache we just finished constructing, to avoid
	 * infinite loops, but we leave the cache marked stale so that we'll
	 * rebuild it again on next access.  Otherwise, we mark the cache valid.
	 */
	if (EventTriggerCacheState == ETCS_REBUILD_STARTED)
		EventTriggerCacheState = ETCS_VALID;
}