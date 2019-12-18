#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int natts; } ;
struct TYPE_14__ {void* fn_oid; } ;
struct TYPE_13__ {void** supportCollation; TYPE_7__* fetchFn; TYPE_7__* distanceFn; TYPE_7__* equalFn; TYPE_7__* picksplitFn; TYPE_7__* penaltyFn; TYPE_7__* decompressFn; TYPE_7__* compressFn; TYPE_7__* unionFn; TYPE_7__* consistentFn; TYPE_9__* nonLeafTupdesc; TYPE_10__* leafTupdesc; void* tempCxt; void* scanCxt; } ;
struct TYPE_12__ {TYPE_10__* rd_att; void** rd_indcollation; } ;
struct TYPE_11__ {int natts; } ;
typedef  TYPE_1__* Relation ;
typedef  void* MemoryContext ;
typedef  TYPE_2__ GISTSTATE ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 void* AllocSetContextCreate (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_9__* CreateTupleDescCopyConstr (TYPE_10__*) ; 
 int /*<<< orphan*/  CurrentMemoryContext ; 
 void* DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GIST_COMPRESS_PROC ; 
 int /*<<< orphan*/  GIST_CONSISTENT_PROC ; 
 int /*<<< orphan*/  GIST_DECOMPRESS_PROC ; 
 int /*<<< orphan*/  GIST_DISTANCE_PROC ; 
 int /*<<< orphan*/  GIST_EQUAL_PROC ; 
 int /*<<< orphan*/  GIST_FETCH_PROC ; 
 int /*<<< orphan*/  GIST_PENALTY_PROC ; 
 int /*<<< orphan*/  GIST_PICKSPLIT_PROC ; 
 int /*<<< orphan*/  GIST_UNION_PROC ; 
 int INDEX_MAX_KEYS ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_1__*) ; 
 void* InvalidOid ; 
 void* MemoryContextSwitchTo (void*) ; 
 scalar_t__ OidIsValid (void*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  fmgr_info_copy (TYPE_7__*,int /*<<< orphan*/ ,void*) ; 
 void* index_getprocid (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_getprocinfo (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ palloc (int) ; 

GISTSTATE *
initGISTstate(Relation index)
{
	GISTSTATE  *giststate;
	MemoryContext scanCxt;
	MemoryContext oldCxt;
	int			i;

	/* safety check to protect fixed-size arrays in GISTSTATE */
	if (index->rd_att->natts > INDEX_MAX_KEYS)
		elog(ERROR, "numberOfAttributes %d > %d",
			 index->rd_att->natts, INDEX_MAX_KEYS);

	/* Create the memory context that will hold the GISTSTATE */
	scanCxt = AllocSetContextCreate(CurrentMemoryContext,
									"GiST scan context",
									ALLOCSET_DEFAULT_SIZES);
	oldCxt = MemoryContextSwitchTo(scanCxt);

	/* Create and fill in the GISTSTATE */
	giststate = (GISTSTATE *) palloc(sizeof(GISTSTATE));

	giststate->scanCxt = scanCxt;
	giststate->tempCxt = scanCxt;	/* caller must change this if needed */
	giststate->leafTupdesc = index->rd_att;

	/*
	 * The truncated tupdesc for non-leaf index tuples, which doesn't contain
	 * the INCLUDE attributes.
	 *
	 * It is used to form tuples during tuple adjustment and page split.
	 * B-tree creates shortened tuple descriptor for every truncated tuple,
	 * because it is doing this less often: it does not have to form truncated
	 * tuples during page split.  Also, B-tree is not adjusting tuples on
	 * internal pages the way GiST does.
	 */
	giststate->nonLeafTupdesc = CreateTupleDescCopyConstr(index->rd_att);
	giststate->nonLeafTupdesc->natts =
		IndexRelationGetNumberOfKeyAttributes(index);

	for (i = 0; i < IndexRelationGetNumberOfKeyAttributes(index); i++)
	{
		fmgr_info_copy(&(giststate->consistentFn[i]),
					   index_getprocinfo(index, i + 1, GIST_CONSISTENT_PROC),
					   scanCxt);
		fmgr_info_copy(&(giststate->unionFn[i]),
					   index_getprocinfo(index, i + 1, GIST_UNION_PROC),
					   scanCxt);

		/* opclasses are not required to provide a Compress method */
		if (OidIsValid(index_getprocid(index, i + 1, GIST_COMPRESS_PROC)))
			fmgr_info_copy(&(giststate->compressFn[i]),
						   index_getprocinfo(index, i + 1, GIST_COMPRESS_PROC),
						   scanCxt);
		else
			giststate->compressFn[i].fn_oid = InvalidOid;

		/* opclasses are not required to provide a Decompress method */
		if (OidIsValid(index_getprocid(index, i + 1, GIST_DECOMPRESS_PROC)))
			fmgr_info_copy(&(giststate->decompressFn[i]),
						   index_getprocinfo(index, i + 1, GIST_DECOMPRESS_PROC),
						   scanCxt);
		else
			giststate->decompressFn[i].fn_oid = InvalidOid;

		fmgr_info_copy(&(giststate->penaltyFn[i]),
					   index_getprocinfo(index, i + 1, GIST_PENALTY_PROC),
					   scanCxt);
		fmgr_info_copy(&(giststate->picksplitFn[i]),
					   index_getprocinfo(index, i + 1, GIST_PICKSPLIT_PROC),
					   scanCxt);
		fmgr_info_copy(&(giststate->equalFn[i]),
					   index_getprocinfo(index, i + 1, GIST_EQUAL_PROC),
					   scanCxt);

		/* opclasses are not required to provide a Distance method */
		if (OidIsValid(index_getprocid(index, i + 1, GIST_DISTANCE_PROC)))
			fmgr_info_copy(&(giststate->distanceFn[i]),
						   index_getprocinfo(index, i + 1, GIST_DISTANCE_PROC),
						   scanCxt);
		else
			giststate->distanceFn[i].fn_oid = InvalidOid;

		/* opclasses are not required to provide a Fetch method */
		if (OidIsValid(index_getprocid(index, i + 1, GIST_FETCH_PROC)))
			fmgr_info_copy(&(giststate->fetchFn[i]),
						   index_getprocinfo(index, i + 1, GIST_FETCH_PROC),
						   scanCxt);
		else
			giststate->fetchFn[i].fn_oid = InvalidOid;

		/*
		 * If the index column has a specified collation, we should honor that
		 * while doing comparisons.  However, we may have a collatable storage
		 * type for a noncollatable indexed data type.  If there's no index
		 * collation then specify default collation in case the support
		 * functions need collation.  This is harmless if the support
		 * functions don't care about collation, so we just do it
		 * unconditionally.  (We could alternatively call get_typcollation,
		 * but that seems like expensive overkill --- there aren't going to be
		 * any cases where a GiST storage type has a nondefault collation.)
		 */
		if (OidIsValid(index->rd_indcollation[i]))
			giststate->supportCollation[i] = index->rd_indcollation[i];
		else
			giststate->supportCollation[i] = DEFAULT_COLLATION_OID;
	}

	/* No opclass information for INCLUDE attributes */
	for (; i < index->rd_att->natts; i++)
	{
		giststate->consistentFn[i].fn_oid = InvalidOid;
		giststate->unionFn[i].fn_oid = InvalidOid;
		giststate->compressFn[i].fn_oid = InvalidOid;
		giststate->decompressFn[i].fn_oid = InvalidOid;
		giststate->penaltyFn[i].fn_oid = InvalidOid;
		giststate->picksplitFn[i].fn_oid = InvalidOid;
		giststate->equalFn[i].fn_oid = InvalidOid;
		giststate->distanceFn[i].fn_oid = InvalidOid;
		giststate->fetchFn[i].fn_oid = InvalidOid;
		giststate->supportCollation[i] = InvalidOid;
	}

	MemoryContextSwitchTo(oldCxt);

	return giststate;
}