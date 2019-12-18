#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
struct TYPE_31__ {int indisvalid; int indisready; int indislive; int indcheckxmin; } ;
struct TYPE_30__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_29__ {int ii_Unique; int /*<<< orphan*/  ii_BrokenHotChain; int /*<<< orphan*/ * ii_ExclusionStrats; int /*<<< orphan*/ * ii_ExclusionProcs; int /*<<< orphan*/ * ii_ExclusionOps; } ;
struct TYPE_28__ {TYPE_1__* rd_rel; } ;
struct TYPE_27__ {scalar_t__ relkind; int /*<<< orphan*/  relam; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  PGRUsage ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ IndexInfo ;
typedef  TYPE_4__* HeapTuple ;
typedef  TYPE_5__* Form_pg_index ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 TYPE_3__* BuildIndexInfo (TYPE_2__*) ; 
 int /*<<< orphan*/  CacheInvalidateRelcache (TYPE_2__*) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  CheckTableNotInUse (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int EarlyPruningEnabled (TYPE_2__*) ; 
 scalar_t__ GETSTRUCT (TYPE_4__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_4__*) ; 
 int /*<<< orphan*/  INDEXRELID ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  IndexGetRelation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IndexRelationId ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_FINALLY () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  PROGRESS_COMMAND_CREATE_INDEX ; 
 int /*<<< orphan*/  PROGRESS_CREATEIDX_ACCESS_METHOD_OID ; 
 int /*<<< orphan*/  PROGRESS_CREATEIDX_COMMAND ; 
 int /*<<< orphan*/  PROGRESS_CREATEIDX_COMMAND_REINDEX ; 
 int /*<<< orphan*/  PROGRESS_CREATEIDX_INDEX_OID ; 
 int REINDEXOPT_REPORT_PROGRESS ; 
 int REINDEXOPT_VERBOSE ; 
 scalar_t__ RELATION_IS_OTHER_TEMP (TYPE_2__*) ; 
 scalar_t__ RELKIND_PARTITIONED_INDEX ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationSetNewRelfilenode (TYPE_2__*,char) ; 
 int /*<<< orphan*/  ResetReindexProcessing () ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_4__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetReindexProcessing (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShareLock ; 
 int /*<<< orphan*/  TransferPredicateLocksToHeapRelation (TYPE_2__*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail_internal (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_build (TYPE_2__*,TYPE_2__*,TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  index_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pg_rusage_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pg_rusage_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pgstat_progress_end_command () ; 
 int /*<<< orphan*/  pgstat_progress_start_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgstat_progress_update_param (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
reindex_index(Oid indexId, bool skip_constraint_checks, char persistence,
			  int options)
{
	Relation	iRel,
				heapRelation;
	Oid			heapId;
	IndexInfo  *indexInfo;
	volatile bool skipped_constraint = false;
	PGRUsage	ru0;
	bool		progress = (options & REINDEXOPT_REPORT_PROGRESS) != 0;

	pg_rusage_init(&ru0);

	/*
	 * Open and lock the parent heap relation.  ShareLock is sufficient since
	 * we only need to be sure no schema or data changes are going on.
	 */
	heapId = IndexGetRelation(indexId, false);
	heapRelation = table_open(heapId, ShareLock);

	if (progress)
	{
		pgstat_progress_start_command(PROGRESS_COMMAND_CREATE_INDEX,
									  heapId);
		pgstat_progress_update_param(PROGRESS_CREATEIDX_COMMAND,
									 PROGRESS_CREATEIDX_COMMAND_REINDEX);
		pgstat_progress_update_param(PROGRESS_CREATEIDX_INDEX_OID,
									 indexId);
	}

	/*
	 * Open the target index relation and get an exclusive lock on it, to
	 * ensure that no one else is touching this particular index.
	 */
	iRel = index_open(indexId, AccessExclusiveLock);

	if (progress)
		pgstat_progress_update_param(PROGRESS_CREATEIDX_ACCESS_METHOD_OID,
									 iRel->rd_rel->relam);

	/*
	 * The case of reindexing partitioned tables and indexes is handled
	 * differently by upper layers, so this case shouldn't arise.
	 */
	if (iRel->rd_rel->relkind == RELKIND_PARTITIONED_INDEX)
		elog(ERROR, "unsupported relation kind for index \"%s\"",
			 RelationGetRelationName(iRel));

	/*
	 * Don't allow reindex on temp tables of other backends ... their local
	 * buffer manager is not going to cope.
	 */
	if (RELATION_IS_OTHER_TEMP(iRel))
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot reindex temporary tables of other sessions")));

	/*
	 * Also check for active uses of the index in the current transaction; we
	 * don't want to reindex underneath an open indexscan.
	 */
	CheckTableNotInUse(iRel, "REINDEX INDEX");

	/*
	 * All predicate locks on the index are about to be made invalid. Promote
	 * them to relation locks on the heap.
	 */
	TransferPredicateLocksToHeapRelation(iRel);

	/* Fetch info needed for index_build */
	indexInfo = BuildIndexInfo(iRel);

	/* If requested, skip checking uniqueness/exclusion constraints */
	if (skip_constraint_checks)
	{
		if (indexInfo->ii_Unique || indexInfo->ii_ExclusionOps != NULL)
			skipped_constraint = true;
		indexInfo->ii_Unique = false;
		indexInfo->ii_ExclusionOps = NULL;
		indexInfo->ii_ExclusionProcs = NULL;
		indexInfo->ii_ExclusionStrats = NULL;
	}

	/* ensure SetReindexProcessing state isn't leaked */
	PG_TRY();
	{
		/* Suppress use of the target index while rebuilding it */
		SetReindexProcessing(heapId, indexId);

		/* Create a new physical relation for the index */
		RelationSetNewRelfilenode(iRel, persistence);

		/* Initialize the index and rebuild */
		/* Note: we do not need to re-establish pkey setting */
		index_build(heapRelation, iRel, indexInfo, true, true);
	}
	PG_FINALLY();
	{
		/* Make sure flag gets cleared on error exit */
		ResetReindexProcessing();
	}
	PG_END_TRY();

	/*
	 * If the index is marked invalid/not-ready/dead (ie, it's from a failed
	 * CREATE INDEX CONCURRENTLY, or a DROP INDEX CONCURRENTLY failed midway),
	 * and we didn't skip a uniqueness check, we can now mark it valid.  This
	 * allows REINDEX to be used to clean up in such cases.
	 *
	 * We can also reset indcheckxmin, because we have now done a
	 * non-concurrent index build, *except* in the case where index_build
	 * found some still-broken HOT chains. If it did, and we don't have to
	 * change any of the other flags, we just leave indcheckxmin alone (note
	 * that index_build won't have changed it, because this is a reindex).
	 * This is okay and desirable because not updating the tuple leaves the
	 * index's usability horizon (recorded as the tuple's xmin value) the same
	 * as it was.
	 *
	 * But, if the index was invalid/not-ready/dead and there were broken HOT
	 * chains, we had better force indcheckxmin true, because the normal
	 * argument that the HOT chains couldn't conflict with the index is
	 * suspect for an invalid index.  (A conflict is definitely possible if
	 * the index was dead.  It probably shouldn't happen otherwise, but let's
	 * be conservative.)  In this case advancing the usability horizon is
	 * appropriate.
	 *
	 * Another reason for avoiding unnecessary updates here is that while
	 * reindexing pg_index itself, we must not try to update tuples in it.
	 * pg_index's indexes should always have these flags in their clean state,
	 * so that won't happen.
	 *
	 * If early pruning/vacuuming is enabled for the heap relation, the
	 * usability horizon must be advanced to the current transaction on every
	 * build or rebuild.  pg_index is OK in this regard because catalog tables
	 * are not subject to early cleanup.
	 */
	if (!skipped_constraint)
	{
		Relation	pg_index;
		HeapTuple	indexTuple;
		Form_pg_index indexForm;
		bool		index_bad;
		bool		early_pruning_enabled = EarlyPruningEnabled(heapRelation);

		pg_index = table_open(IndexRelationId, RowExclusiveLock);

		indexTuple = SearchSysCacheCopy1(INDEXRELID,
										 ObjectIdGetDatum(indexId));
		if (!HeapTupleIsValid(indexTuple))
			elog(ERROR, "cache lookup failed for index %u", indexId);
		indexForm = (Form_pg_index) GETSTRUCT(indexTuple);

		index_bad = (!indexForm->indisvalid ||
					 !indexForm->indisready ||
					 !indexForm->indislive);
		if (index_bad ||
			(indexForm->indcheckxmin && !indexInfo->ii_BrokenHotChain) ||
			early_pruning_enabled)
		{
			if (!indexInfo->ii_BrokenHotChain && !early_pruning_enabled)
				indexForm->indcheckxmin = false;
			else if (index_bad || early_pruning_enabled)
				indexForm->indcheckxmin = true;
			indexForm->indisvalid = true;
			indexForm->indisready = true;
			indexForm->indislive = true;
			CatalogTupleUpdate(pg_index, &indexTuple->t_self, indexTuple);

			/*
			 * Invalidate the relcache for the table, so that after we commit
			 * all sessions will refresh the table's index list.  This ensures
			 * that if anyone misses seeing the pg_index row during this
			 * update, they'll refresh their list before attempting any update
			 * on the table.
			 */
			CacheInvalidateRelcache(heapRelation);
		}

		table_close(pg_index, RowExclusiveLock);
	}

	/* Log what we did */
	if (options & REINDEXOPT_VERBOSE)
		ereport(INFO,
				(errmsg("index \"%s\" was reindexed",
						get_rel_name(indexId)),
				 errdetail_internal("%s",
									pg_rusage_show(&ru0))));

	if (progress)
		pgstat_progress_end_command();

	/* Close rels, but keep locks */
	index_close(iRel, NoLock);
	table_close(heapRelation, NoLock);
}