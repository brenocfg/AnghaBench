#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
typedef  scalar_t__ float4 ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_2__ {scalar_t__ relkind; int relhasindex; scalar_t__ relpages; scalar_t__ reltuples; scalar_t__ relallvisible; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_class ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Anum_pg_class_oid ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CacheInvalidateRelcacheByTuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_INDEX ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  RELOID ; 
 scalar_t__ ReindexIsProcessingHeap (int /*<<< orphan*/ ) ; 
 scalar_t__ RelationGetNumberOfBlocks (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_copytuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_inplace_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  visibilitymap_count (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
index_update_stats(Relation rel,
				   bool hasindex,
				   double reltuples)
{
	Oid			relid = RelationGetRelid(rel);
	Relation	pg_class;
	HeapTuple	tuple;
	Form_pg_class rd_rel;
	bool		dirty;

	/*
	 * We always update the pg_class row using a non-transactional,
	 * overwrite-in-place update.  There are several reasons for this:
	 *
	 * 1. In bootstrap mode, we have no choice --- UPDATE wouldn't work.
	 *
	 * 2. We could be reindexing pg_class itself, in which case we can't move
	 * its pg_class row because CatalogTupleInsert/CatalogTupleUpdate might
	 * not know about all the indexes yet (see reindex_relation).
	 *
	 * 3. Because we execute CREATE INDEX with just share lock on the parent
	 * rel (to allow concurrent index creations), an ordinary update could
	 * suffer a tuple-concurrently-updated failure against another CREATE
	 * INDEX committing at about the same time.  We can avoid that by having
	 * them both do nontransactional updates (we assume they will both be
	 * trying to change the pg_class row to the same thing, so it doesn't
	 * matter which goes first).
	 *
	 * It is safe to use a non-transactional update even though our
	 * transaction could still fail before committing.  Setting relhasindex
	 * true is safe even if there are no indexes (VACUUM will eventually fix
	 * it).  And of course the new relpages and reltuples counts are correct
	 * regardless.  However, we don't want to change relpages (or
	 * relallvisible) if the caller isn't providing an updated reltuples
	 * count, because that would bollix the reltuples/relpages ratio which is
	 * what's really important.
	 */

	pg_class = table_open(RelationRelationId, RowExclusiveLock);

	/*
	 * Make a copy of the tuple to update.  Normally we use the syscache, but
	 * we can't rely on that during bootstrap or while reindexing pg_class
	 * itself.
	 */
	if (IsBootstrapProcessingMode() ||
		ReindexIsProcessingHeap(RelationRelationId))
	{
		/* don't assume syscache will work */
		TableScanDesc pg_class_scan;
		ScanKeyData key[1];

		ScanKeyInit(&key[0],
					Anum_pg_class_oid,
					BTEqualStrategyNumber, F_OIDEQ,
					ObjectIdGetDatum(relid));

		pg_class_scan = table_beginscan_catalog(pg_class, 1, key);
		tuple = heap_getnext(pg_class_scan, ForwardScanDirection);
		tuple = heap_copytuple(tuple);
		table_endscan(pg_class_scan);
	}
	else
	{
		/* normal case, use syscache */
		tuple = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(relid));
	}

	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "could not find tuple for relation %u", relid);
	rd_rel = (Form_pg_class) GETSTRUCT(tuple);

	/* Should this be a more comprehensive test? */
	Assert(rd_rel->relkind != RELKIND_PARTITIONED_INDEX);

	/* Apply required updates, if any, to copied tuple */

	dirty = false;
	if (rd_rel->relhasindex != hasindex)
	{
		rd_rel->relhasindex = hasindex;
		dirty = true;
	}

	if (reltuples >= 0)
	{
		BlockNumber relpages = RelationGetNumberOfBlocks(rel);
		BlockNumber relallvisible;

		if (rd_rel->relkind != RELKIND_INDEX)
			visibilitymap_count(rel, &relallvisible, NULL);
		else					/* don't bother for indexes */
			relallvisible = 0;

		if (rd_rel->relpages != (int32) relpages)
		{
			rd_rel->relpages = (int32) relpages;
			dirty = true;
		}
		if (rd_rel->reltuples != (float4) reltuples)
		{
			rd_rel->reltuples = (float4) reltuples;
			dirty = true;
		}
		if (rd_rel->relallvisible != (int32) relallvisible)
		{
			rd_rel->relallvisible = (int32) relallvisible;
			dirty = true;
		}
	}

	/*
	 * If anything changed, write out the tuple
	 */
	if (dirty)
	{
		heap_inplace_update(pg_class, tuple);
		/* the above sends a cache inval message */
	}
	else
	{
		/* no need to change tuple, but force relcache inval anyway */
		CacheInvalidateRelcacheByTuple(tuple);
	}

	heap_freetuple(tuple);

	table_close(pg_class, RowExclusiveLock);
}