#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  TupleDesc ;
struct TYPE_10__ {int /*<<< orphan*/  relisshared; } ;
struct TYPE_9__ {int cc_nkeys; scalar_t__* cc_keyno; int /*<<< orphan*/  cc_tupdesc; int /*<<< orphan*/  cc_relname; TYPE_1__* cc_skey; int /*<<< orphan*/ * cc_fastequal; int /*<<< orphan*/ * cc_hashfunc; int /*<<< orphan*/  cc_relisshared; int /*<<< orphan*/  cc_reloid; } ;
struct TYPE_8__ {int /*<<< orphan*/  attnotnull; int /*<<< orphan*/  atttypid; } ;
struct TYPE_7__ {scalar_t__ sk_attno; int /*<<< orphan*/  sk_collation; int /*<<< orphan*/  sk_subtype; int /*<<< orphan*/  sk_strategy; int /*<<< orphan*/  sk_func; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  RegProcedure ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/ * MemoryContext ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  TYPE_3__ CatCache ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CACHE_elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  C_COLLATION_OID ; 
 int /*<<< orphan*/ * CacheMemoryContext ; 
 int /*<<< orphan*/  CatalogCacheInitializeCache_DEBUG1 ; 
 int /*<<< orphan*/  CatalogCacheInitializeCache_DEBUG2 ; 
 int /*<<< orphan*/  CreateTupleDescCopyConstr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEBUG2 ; 
 int /*<<< orphan*/  FATAL ; 
 int /*<<< orphan*/  GetCCHashEqFuncs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/ * MemoryContextSwitchTo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OIDOID ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 TYPE_5__* RelationGetForm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 TYPE_2__* TupleDescAttr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fmgr_info_cxt (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pstrdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
CatalogCacheInitializeCache(CatCache *cache)
{
	Relation	relation;
	MemoryContext oldcxt;
	TupleDesc	tupdesc;
	int			i;

	CatalogCacheInitializeCache_DEBUG1;

	relation = table_open(cache->cc_reloid, AccessShareLock);

	/*
	 * switch to the cache context so our allocations do not vanish at the end
	 * of a transaction
	 */
	Assert(CacheMemoryContext != NULL);

	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);

	/*
	 * copy the relcache's tuple descriptor to permanent cache storage
	 */
	tupdesc = CreateTupleDescCopyConstr(RelationGetDescr(relation));

	/*
	 * save the relation's name and relisshared flag, too (cc_relname is used
	 * only for debugging purposes)
	 */
	cache->cc_relname = pstrdup(RelationGetRelationName(relation));
	cache->cc_relisshared = RelationGetForm(relation)->relisshared;

	/*
	 * return to the caller's memory context and close the rel
	 */
	MemoryContextSwitchTo(oldcxt);

	table_close(relation, AccessShareLock);

	CACHE_elog(DEBUG2, "CatalogCacheInitializeCache: %s, %d keys",
			   cache->cc_relname, cache->cc_nkeys);

	/*
	 * initialize cache's key information
	 */
	for (i = 0; i < cache->cc_nkeys; ++i)
	{
		Oid			keytype;
		RegProcedure eqfunc;

		CatalogCacheInitializeCache_DEBUG2;

		if (cache->cc_keyno[i] > 0)
		{
			Form_pg_attribute attr = TupleDescAttr(tupdesc,
												   cache->cc_keyno[i] - 1);

			keytype = attr->atttypid;
			/* cache key columns should always be NOT NULL */
			Assert(attr->attnotnull);
		}
		else
		{
			if (cache->cc_keyno[i] < 0)
				elog(FATAL, "sys attributes are not supported in caches");
			keytype = OIDOID;
		}

		GetCCHashEqFuncs(keytype,
						 &cache->cc_hashfunc[i],
						 &eqfunc,
						 &cache->cc_fastequal[i]);

		/*
		 * Do equality-function lookup (we assume this won't need a catalog
		 * lookup for any supported type)
		 */
		fmgr_info_cxt(eqfunc,
					  &cache->cc_skey[i].sk_func,
					  CacheMemoryContext);

		/* Initialize sk_attno suitably for HeapKeyTest() and heap scans */
		cache->cc_skey[i].sk_attno = cache->cc_keyno[i];

		/* Fill in sk_strategy as well --- always standard equality */
		cache->cc_skey[i].sk_strategy = BTEqualStrategyNumber;
		cache->cc_skey[i].sk_subtype = InvalidOid;
		/* If a catcache key requires a collation, it must be C collation */
		cache->cc_skey[i].sk_collation = C_COLLATION_OID;

		CACHE_elog(DEBUG2, "CatalogCacheInitializeCache %s %d %p",
				   cache->cc_relname, i, cache);
	}

	/*
	 * mark this cache fully initialized
	 */
	cache->cc_tupdesc = tupdesc;
}