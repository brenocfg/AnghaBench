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
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_9__ {int /*<<< orphan*/  prslextype; int /*<<< orphan*/  prsheadline; int /*<<< orphan*/  prsend; int /*<<< orphan*/  prstoken; int /*<<< orphan*/  prsstart; } ;
struct TYPE_8__ {int keysize; int entrysize; scalar_t__ prsId; int isvalid; int /*<<< orphan*/  prsheadline; int /*<<< orphan*/  headlineOid; int /*<<< orphan*/  prsend; int /*<<< orphan*/  endOid; int /*<<< orphan*/  prstoken; int /*<<< orphan*/  tokenOid; int /*<<< orphan*/  prsstart; int /*<<< orphan*/  startOid; int /*<<< orphan*/  lextypeOid; } ;
typedef  TYPE_1__ TSParserCacheEntry ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ HASHCTL ;
typedef  TYPE_3__* Form_pg_ts_parser ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateTSCacheCallBack ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TSPARSEROID ; 
 int /*<<< orphan*/ * TSParserCacheHash ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  fmgr_info_cxt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_1__*,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* lastUsedParser ; 

TSParserCacheEntry *
lookup_ts_parser_cache(Oid prsId)
{
	TSParserCacheEntry *entry;

	if (TSParserCacheHash == NULL)
	{
		/* First time through: initialize the hash table */
		HASHCTL		ctl;

		MemSet(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(Oid);
		ctl.entrysize = sizeof(TSParserCacheEntry);
		TSParserCacheHash = hash_create("Tsearch parser cache", 4,
										&ctl, HASH_ELEM | HASH_BLOBS);
		/* Flush cache on pg_ts_parser changes */
		CacheRegisterSyscacheCallback(TSPARSEROID, InvalidateTSCacheCallBack,
									  PointerGetDatum(TSParserCacheHash));

		/* Also make sure CacheMemoryContext exists */
		if (!CacheMemoryContext)
			CreateCacheMemoryContext();
	}

	/* Check single-entry cache */
	if (lastUsedParser && lastUsedParser->prsId == prsId &&
		lastUsedParser->isvalid)
		return lastUsedParser;

	/* Try to look up an existing entry */
	entry = (TSParserCacheEntry *) hash_search(TSParserCacheHash,
											   (void *) &prsId,
											   HASH_FIND, NULL);
	if (entry == NULL || !entry->isvalid)
	{
		/*
		 * If we didn't find one, we want to make one. But first look up the
		 * object to be sure the OID is real.
		 */
		HeapTuple	tp;
		Form_pg_ts_parser prs;

		tp = SearchSysCache1(TSPARSEROID, ObjectIdGetDatum(prsId));
		if (!HeapTupleIsValid(tp))
			elog(ERROR, "cache lookup failed for text search parser %u",
				 prsId);
		prs = (Form_pg_ts_parser) GETSTRUCT(tp);

		/*
		 * Sanity checks
		 */
		if (!OidIsValid(prs->prsstart))
			elog(ERROR, "text search parser %u has no prsstart method", prsId);
		if (!OidIsValid(prs->prstoken))
			elog(ERROR, "text search parser %u has no prstoken method", prsId);
		if (!OidIsValid(prs->prsend))
			elog(ERROR, "text search parser %u has no prsend method", prsId);

		if (entry == NULL)
		{
			bool		found;

			/* Now make the cache entry */
			entry = (TSParserCacheEntry *)
				hash_search(TSParserCacheHash,
							(void *) &prsId,
							HASH_ENTER, &found);
			Assert(!found);		/* it wasn't there a moment ago */
		}

		MemSet(entry, 0, sizeof(TSParserCacheEntry));
		entry->prsId = prsId;
		entry->startOid = prs->prsstart;
		entry->tokenOid = prs->prstoken;
		entry->endOid = prs->prsend;
		entry->headlineOid = prs->prsheadline;
		entry->lextypeOid = prs->prslextype;

		ReleaseSysCache(tp);

		fmgr_info_cxt(entry->startOid, &entry->prsstart, CacheMemoryContext);
		fmgr_info_cxt(entry->tokenOid, &entry->prstoken, CacheMemoryContext);
		fmgr_info_cxt(entry->endOid, &entry->prsend, CacheMemoryContext);
		if (OidIsValid(entry->headlineOid))
			fmgr_info_cxt(entry->headlineOid, &entry->prsheadline,
						  CacheMemoryContext);

		entry->isvalid = true;
	}

	lastUsedParser = entry;

	return entry;
}