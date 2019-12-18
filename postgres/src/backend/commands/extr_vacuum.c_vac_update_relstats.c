#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int32 ;
typedef  scalar_t__ float4 ;
typedef  int /*<<< orphan*/  TransactionId ;
struct TYPE_9__ {scalar_t__ relpages; scalar_t__ reltuples; scalar_t__ relallvisible; int relhasindex; int relhasrules; int relhastriggers; int /*<<< orphan*/  relminmxid; int /*<<< orphan*/  relfrozenxid; } ;
struct TYPE_8__ {int /*<<< orphan*/ * trigdesc; int /*<<< orphan*/ * rd_rules; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  MultiXactId ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_2__* Form_pg_class ;
typedef  scalar_t__ BlockNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ MultiXactIdIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ MultiXactIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  ReadNewTransactionId () ; 
 int /*<<< orphan*/  ReadNextMultiXactId () ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdIsNormal (int /*<<< orphan*/ ) ; 
 scalar_t__ TransactionIdPrecedes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_inplace_update (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
vac_update_relstats(Relation relation,
					BlockNumber num_pages, double num_tuples,
					BlockNumber num_all_visible_pages,
					bool hasindex, TransactionId frozenxid,
					MultiXactId minmulti,
					bool in_outer_xact)
{
	Oid			relid = RelationGetRelid(relation);
	Relation	rd;
	HeapTuple	ctup;
	Form_pg_class pgcform;
	bool		dirty;

	rd = table_open(RelationRelationId, RowExclusiveLock);

	/* Fetch a copy of the tuple to scribble on */
	ctup = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(relid));
	if (!HeapTupleIsValid(ctup))
		elog(ERROR, "pg_class entry for relid %u vanished during vacuuming",
			 relid);
	pgcform = (Form_pg_class) GETSTRUCT(ctup);

	/* Apply statistical updates, if any, to copied tuple */

	dirty = false;
	if (pgcform->relpages != (int32) num_pages)
	{
		pgcform->relpages = (int32) num_pages;
		dirty = true;
	}
	if (pgcform->reltuples != (float4) num_tuples)
	{
		pgcform->reltuples = (float4) num_tuples;
		dirty = true;
	}
	if (pgcform->relallvisible != (int32) num_all_visible_pages)
	{
		pgcform->relallvisible = (int32) num_all_visible_pages;
		dirty = true;
	}

	/* Apply DDL updates, but not inside an outer transaction (see above) */

	if (!in_outer_xact)
	{
		/*
		 * If we didn't find any indexes, reset relhasindex.
		 */
		if (pgcform->relhasindex && !hasindex)
		{
			pgcform->relhasindex = false;
			dirty = true;
		}

		/* We also clear relhasrules and relhastriggers if needed */
		if (pgcform->relhasrules && relation->rd_rules == NULL)
		{
			pgcform->relhasrules = false;
			dirty = true;
		}
		if (pgcform->relhastriggers && relation->trigdesc == NULL)
		{
			pgcform->relhastriggers = false;
			dirty = true;
		}
	}

	/*
	 * Update relfrozenxid, unless caller passed InvalidTransactionId
	 * indicating it has no new data.
	 *
	 * Ordinarily, we don't let relfrozenxid go backwards: if things are
	 * working correctly, the only way the new frozenxid could be older would
	 * be if a previous VACUUM was done with a tighter freeze_min_age, in
	 * which case we don't want to forget the work it already did.  However,
	 * if the stored relfrozenxid is "in the future", then it must be corrupt
	 * and it seems best to overwrite it with the cutoff we used this time.
	 * This should match vac_update_datfrozenxid() concerning what we consider
	 * to be "in the future".
	 */
	if (TransactionIdIsNormal(frozenxid) &&
		pgcform->relfrozenxid != frozenxid &&
		(TransactionIdPrecedes(pgcform->relfrozenxid, frozenxid) ||
		 TransactionIdPrecedes(ReadNewTransactionId(),
							   pgcform->relfrozenxid)))
	{
		pgcform->relfrozenxid = frozenxid;
		dirty = true;
	}

	/* Similarly for relminmxid */
	if (MultiXactIdIsValid(minmulti) &&
		pgcform->relminmxid != minmulti &&
		(MultiXactIdPrecedes(pgcform->relminmxid, minmulti) ||
		 MultiXactIdPrecedes(ReadNextMultiXactId(), pgcform->relminmxid)))
	{
		pgcform->relminmxid = minmulti;
		dirty = true;
	}

	/* If anything changed, write out the tuple. */
	if (dirty)
		heap_inplace_update(rd, ctup);

	table_close(rd, RowExclusiveLock);
}