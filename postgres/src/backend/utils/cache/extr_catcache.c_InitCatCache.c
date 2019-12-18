#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dlist_head ;
typedef  scalar_t__ TupleDesc ;
struct TYPE_6__ {int id; char* cc_relname; int cc_relisshared; int cc_nbuckets; int cc_nkeys; int* cc_keyno; int /*<<< orphan*/  cc_next; scalar_t__ cc_ntup; scalar_t__ cc_tupdesc; void* cc_indexoid; void* cc_reloid; int /*<<< orphan*/  cc_bucket; } ;
struct TYPE_5__ {int /*<<< orphan*/  ch_caches; scalar_t__ ch_ntup; } ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  MemoryContext ;
typedef  TYPE_1__ CatCacheHeader ;
typedef  TYPE_2__ CatCache ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ CACHELINEALIGN (int /*<<< orphan*/ ) ; 
 TYPE_1__* CacheHdr ; 
 int /*<<< orphan*/  CacheMemoryContext ; 
 int /*<<< orphan*/  CatCachePrintStats ; 
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 int /*<<< orphan*/  InitCatCache_DEBUG2 ; 
 int /*<<< orphan*/  MemoryContextSwitchTo (int /*<<< orphan*/ ) ; 
 int PG_CACHE_LINE_SIZE ; 
 int /*<<< orphan*/  on_proc_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 
 int /*<<< orphan*/  palloc0 (int) ; 
 int /*<<< orphan*/  slist_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slist_push_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

CatCache *
InitCatCache(int id,
			 Oid reloid,
			 Oid indexoid,
			 int nkeys,
			 const int *key,
			 int nbuckets)
{
	CatCache   *cp;
	MemoryContext oldcxt;
	size_t		sz;
	int			i;

	/*
	 * nbuckets is the initial number of hash buckets to use in this catcache.
	 * It will be enlarged later if it becomes too full.
	 *
	 * nbuckets must be a power of two.  We check this via Assert rather than
	 * a full runtime check because the values will be coming from constant
	 * tables.
	 *
	 * If you're confused by the power-of-two check, see comments in
	 * bitmapset.c for an explanation.
	 */
	Assert(nbuckets > 0 && (nbuckets & -nbuckets) == nbuckets);

	/*
	 * first switch to the cache context so our allocations do not vanish at
	 * the end of a transaction
	 */
	if (!CacheMemoryContext)
		CreateCacheMemoryContext();

	oldcxt = MemoryContextSwitchTo(CacheMemoryContext);

	/*
	 * if first time through, initialize the cache group header
	 */
	if (CacheHdr == NULL)
	{
		CacheHdr = (CatCacheHeader *) palloc(sizeof(CatCacheHeader));
		slist_init(&CacheHdr->ch_caches);
		CacheHdr->ch_ntup = 0;
#ifdef CATCACHE_STATS
		/* set up to dump stats at backend exit */
		on_proc_exit(CatCachePrintStats, 0);
#endif
	}

	/*
	 * Allocate a new cache structure, aligning to a cacheline boundary
	 *
	 * Note: we rely on zeroing to initialize all the dlist headers correctly
	 */
	sz = sizeof(CatCache) + PG_CACHE_LINE_SIZE;
	cp = (CatCache *) CACHELINEALIGN(palloc0(sz));
	cp->cc_bucket = palloc0(nbuckets * sizeof(dlist_head));

	/*
	 * initialize the cache's relation information for the relation
	 * corresponding to this cache, and initialize some of the new cache's
	 * other internal fields.  But don't open the relation yet.
	 */
	cp->id = id;
	cp->cc_relname = "(not known yet)";
	cp->cc_reloid = reloid;
	cp->cc_indexoid = indexoid;
	cp->cc_relisshared = false; /* temporary */
	cp->cc_tupdesc = (TupleDesc) NULL;
	cp->cc_ntup = 0;
	cp->cc_nbuckets = nbuckets;
	cp->cc_nkeys = nkeys;
	for (i = 0; i < nkeys; ++i)
		cp->cc_keyno[i] = key[i];

	/*
	 * new cache is initialized as far as we can go for now. print some
	 * debugging information, if appropriate.
	 */
	InitCatCache_DEBUG2;

	/*
	 * add completed cache to top of group header's list
	 */
	slist_push_head(&CacheHdr->ch_caches, &cp->cc_next);

	/*
	 * back to the old context before we return...
	 */
	MemoryContextSwitchTo(oldcxt);

	return cp;
}