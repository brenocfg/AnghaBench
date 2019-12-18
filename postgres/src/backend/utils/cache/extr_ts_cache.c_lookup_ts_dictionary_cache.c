#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ctl ;
struct TYPE_11__ {scalar_t__ dicttemplate; int /*<<< orphan*/  dictname; } ;
struct TYPE_10__ {scalar_t__ tmpllexize; scalar_t__ tmplinit; } ;
struct TYPE_9__ {int keysize; int entrysize; scalar_t__ dictId; int isvalid; scalar_t__ lexizeOid; int /*<<< orphan*/  dictCtx; int /*<<< orphan*/  lexize; int /*<<< orphan*/  dictData; } ;
typedef  TYPE_1__ TSDictionaryCacheEntry ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__ HASHCTL ;
typedef  TYPE_3__* Form_pg_ts_template ;
typedef  TYPE_4__* Form_pg_ts_dict ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_SMALL_SIZES ; 
 int /*<<< orphan*/  AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Anum_pg_ts_dict_dictinitoption ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CacheRegisterSyscacheCallback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 int /*<<< orphan*/  DatumGetPointer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int HASH_BLOBS ; 
 int HASH_ELEM ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InvalidateTSCacheCallBack ; 
 int /*<<< orphan*/  MemSet (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MemoryContextCopyAndSetIdentifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextReset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MemoryContextSetIdentifier (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NIL ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  OidFunctionCall1 (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  TSDICTOID ; 
 int /*<<< orphan*/ * TSDictionaryCacheHash ; 
 int /*<<< orphan*/  TSTEMPLATEOID ; 
 int /*<<< orphan*/ * deserialize_deflist (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  fmgr_info_cxt (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hash_create (char*,int,TYPE_1__*,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* lastUsedDictionary ; 

TSDictionaryCacheEntry *
lookup_ts_dictionary_cache(Oid dictId)
{
	TSDictionaryCacheEntry *entry;

	if (TSDictionaryCacheHash == NULL)
	{
		/* First time through: initialize the hash table */
		HASHCTL		ctl;

		MemSet(&ctl, 0, sizeof(ctl));
		ctl.keysize = sizeof(Oid);
		ctl.entrysize = sizeof(TSDictionaryCacheEntry);
		TSDictionaryCacheHash = hash_create("Tsearch dictionary cache", 8,
											&ctl, HASH_ELEM | HASH_BLOBS);
		/* Flush cache on pg_ts_dict and pg_ts_template changes */
		CacheRegisterSyscacheCallback(TSDICTOID, InvalidateTSCacheCallBack,
									  PointerGetDatum(TSDictionaryCacheHash));
		CacheRegisterSyscacheCallback(TSTEMPLATEOID, InvalidateTSCacheCallBack,
									  PointerGetDatum(TSDictionaryCacheHash));

		/* Also make sure CacheMemoryContext exists */
		if (!CacheMemoryContext)
			CreateCacheMemoryContext();
	}

	/* Check single-entry cache */
	if (lastUsedDictionary && lastUsedDictionary->dictId == dictId &&
		lastUsedDictionary->isvalid)
		return lastUsedDictionary;

	/* Try to look up an existing entry */
	entry = (TSDictionaryCacheEntry *) hash_search(TSDictionaryCacheHash,
												   (void *) &dictId,
												   HASH_FIND, NULL);
	if (entry == NULL || !entry->isvalid)
	{
		/*
		 * If we didn't find one, we want to make one. But first look up the
		 * object to be sure the OID is real.
		 */
		HeapTuple	tpdict,
					tptmpl;
		Form_pg_ts_dict dict;
		Form_pg_ts_template template;
		MemoryContext saveCtx;

		tpdict = SearchSysCache1(TSDICTOID, ObjectIdGetDatum(dictId));
		if (!HeapTupleIsValid(tpdict))
			elog(ERROR, "cache lookup failed for text search dictionary %u",
				 dictId);
		dict = (Form_pg_ts_dict) GETSTRUCT(tpdict);

		/*
		 * Sanity checks
		 */
		if (!OidIsValid(dict->dicttemplate))
			elog(ERROR, "text search dictionary %u has no template", dictId);

		/*
		 * Retrieve dictionary's template
		 */
		tptmpl = SearchSysCache1(TSTEMPLATEOID,
								 ObjectIdGetDatum(dict->dicttemplate));
		if (!HeapTupleIsValid(tptmpl))
			elog(ERROR, "cache lookup failed for text search template %u",
				 dict->dicttemplate);
		template = (Form_pg_ts_template) GETSTRUCT(tptmpl);

		/*
		 * Sanity checks
		 */
		if (!OidIsValid(template->tmpllexize))
			elog(ERROR, "text search template %u has no lexize method",
				 template->tmpllexize);

		if (entry == NULL)
		{
			bool		found;

			/* Now make the cache entry */
			entry = (TSDictionaryCacheEntry *)
				hash_search(TSDictionaryCacheHash,
							(void *) &dictId,
							HASH_ENTER, &found);
			Assert(!found);		/* it wasn't there a moment ago */

			/* Create private memory context the first time through */
			saveCtx = AllocSetContextCreate(CacheMemoryContext,
											"TS dictionary",
											ALLOCSET_SMALL_SIZES);
			MemoryContextCopyAndSetIdentifier(saveCtx, NameStr(dict->dictname));
		}
		else
		{
			/* Clear the existing entry's private context */
			saveCtx = entry->dictCtx;
			/* Don't let context's ident pointer dangle while we reset it */
			MemoryContextSetIdentifier(saveCtx, NULL);
			MemoryContextReset(saveCtx);
			MemoryContextCopyAndSetIdentifier(saveCtx, NameStr(dict->dictname));
		}

		MemSet(entry, 0, sizeof(TSDictionaryCacheEntry));
		entry->dictId = dictId;
		entry->dictCtx = saveCtx;

		entry->lexizeOid = template->tmpllexize;

		if (OidIsValid(template->tmplinit))
		{
			List	   *dictoptions;
			Datum		opt;
			bool		isnull;
			MemoryContext oldcontext;

			/*
			 * Init method runs in dictionary's private memory context, and we
			 * make sure the options are stored there too
			 */
			oldcontext = MemoryContextSwitchTo(entry->dictCtx);

			opt = SysCacheGetAttr(TSDICTOID, tpdict,
								  Anum_pg_ts_dict_dictinitoption,
								  &isnull);
			if (isnull)
				dictoptions = NIL;
			else
				dictoptions = deserialize_deflist(opt);

			entry->dictData =
				DatumGetPointer(OidFunctionCall1(template->tmplinit,
												 PointerGetDatum(dictoptions)));

			MemoryContextSwitchTo(oldcontext);
		}

		ReleaseSysCache(tptmpl);
		ReleaseSysCache(tpdict);

		fmgr_info_cxt(entry->lexizeOid, &entry->lexize, entry->dictCtx);

		entry->isvalid = true;
	}

	lastUsedDictionary = entry;

	return entry;
}