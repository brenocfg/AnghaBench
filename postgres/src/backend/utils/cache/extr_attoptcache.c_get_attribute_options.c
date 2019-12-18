#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  bytea ;
struct TYPE_5__ {int /*<<< orphan*/ * opts; } ;
struct TYPE_4__ {int attnum; int /*<<< orphan*/  attrelid; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;
typedef  int /*<<< orphan*/  AttributeOpts ;
typedef  TYPE_1__ AttoptCacheKey ;
typedef  TYPE_2__ AttoptCacheEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int /*<<< orphan*/  Anum_pg_attribute_attoptions ; 
 int /*<<< orphan*/  AttoptCacheHash ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  HASH_ENTER ; 
 int /*<<< orphan*/  HASH_FIND ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitializeAttoptCache () ; 
 int /*<<< orphan*/  Int16GetDatum (int) ; 
 int /*<<< orphan*/ * MemoryContextAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysCacheGetAttr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  VARSIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * attribute_reloptions (int /*<<< orphan*/ ,int) ; 
 scalar_t__ hash_search (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * palloc (int /*<<< orphan*/ ) ; 

AttributeOpts *
get_attribute_options(Oid attrelid, int attnum)
{
	AttoptCacheKey key;
	AttoptCacheEntry *attopt;
	AttributeOpts *result;
	HeapTuple	tp;

	/* Find existing cache entry, if any. */
	if (!AttoptCacheHash)
		InitializeAttoptCache();
	memset(&key, 0, sizeof(key));	/* make sure any padding bits are unset */
	key.attrelid = attrelid;
	key.attnum = attnum;
	attopt =
		(AttoptCacheEntry *) hash_search(AttoptCacheHash,
										 (void *) &key,
										 HASH_FIND,
										 NULL);

	/* Not found in Attopt cache.  Construct new cache entry. */
	if (!attopt)
	{
		AttributeOpts *opts;

		tp = SearchSysCache2(ATTNUM,
							 ObjectIdGetDatum(attrelid),
							 Int16GetDatum(attnum));

		/*
		 * If we don't find a valid HeapTuple, it must mean someone has
		 * managed to request attribute details for a non-existent attribute.
		 * We treat that case as if no options were specified.
		 */
		if (!HeapTupleIsValid(tp))
			opts = NULL;
		else
		{
			Datum		datum;
			bool		isNull;

			datum = SysCacheGetAttr(ATTNUM,
									tp,
									Anum_pg_attribute_attoptions,
									&isNull);
			if (isNull)
				opts = NULL;
			else
			{
				bytea	   *bytea_opts = attribute_reloptions(datum, false);

				opts = MemoryContextAlloc(CacheMemoryContext,
										  VARSIZE(bytea_opts));
				memcpy(opts, bytea_opts, VARSIZE(bytea_opts));
			}
			ReleaseSysCache(tp);
		}

		/*
		 * It's important to create the actual cache entry only after reading
		 * pg_attribute, since the read could cause a cache flush.
		 */
		attopt = (AttoptCacheEntry *) hash_search(AttoptCacheHash,
												  (void *) &key,
												  HASH_ENTER,
												  NULL);
		attopt->opts = opts;
	}

	/* Return results in caller's memory context. */
	if (attopt->opts == NULL)
		return NULL;
	result = palloc(VARSIZE(attopt->opts));
	memcpy(result, attopt->opts, VARSIZE(attopt->opts));
	return result;
}