#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  nulls ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  SnapshotData ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  scalar_t__ RepOriginId ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/ * HeapTuple ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int Anum_pg_replication_origin_roident ; 
 int Anum_pg_replication_origin_roname ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CHECK_FOR_INTERRUPTS () ; 
 int /*<<< orphan*/  CStringGetTextDatum (char*) ; 
 int /*<<< orphan*/  CatalogTupleInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CommandCounterIncrement () ; 
 int /*<<< orphan*/  ERRCODE_PROGRAM_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExclusiveLock ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 int HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitDirtySnapshot (int /*<<< orphan*/ ) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  IsTransactionState () ; 
 int Natts_pg_replication_origin ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ PG_UINT16_MAX ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReplicationOriginIdentIndex ; 
 int /*<<< orphan*/  ReplicationOriginRelationId ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/ * heap_form_tuple (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

RepOriginId
replorigin_create(char *roname)
{
	Oid			roident;
	HeapTuple	tuple = NULL;
	Relation	rel;
	Datum		roname_d;
	SnapshotData SnapshotDirty;
	SysScanDesc scan;
	ScanKeyData key;

	roname_d = CStringGetTextDatum(roname);

	Assert(IsTransactionState());

	/*
	 * We need the numeric replication origin to be 16bit wide, so we cannot
	 * rely on the normal oid allocation. Instead we simply scan
	 * pg_replication_origin for the first unused id. That's not particularly
	 * efficient, but this should be a fairly infrequent operation - we can
	 * easily spend a bit more code on this when it turns out it needs to be
	 * faster.
	 *
	 * We handle concurrency by taking an exclusive lock (allowing reads!)
	 * over the table for the duration of the search. Because we use a "dirty
	 * snapshot" we can read rows that other in-progress sessions have
	 * written, even though they would be invisible with normal snapshots. Due
	 * to the exclusive lock there's no danger that new rows can appear while
	 * we're checking.
	 */
	InitDirtySnapshot(SnapshotDirty);

	rel = table_open(ReplicationOriginRelationId, ExclusiveLock);

	for (roident = InvalidOid + 1; roident < PG_UINT16_MAX; roident++)
	{
		bool		nulls[Natts_pg_replication_origin];
		Datum		values[Natts_pg_replication_origin];
		bool		collides;

		CHECK_FOR_INTERRUPTS();

		ScanKeyInit(&key,
					Anum_pg_replication_origin_roident,
					BTEqualStrategyNumber, F_OIDEQ,
					ObjectIdGetDatum(roident));

		scan = systable_beginscan(rel, ReplicationOriginIdentIndex,
								  true /* indexOK */ ,
								  &SnapshotDirty,
								  1, &key);

		collides = HeapTupleIsValid(systable_getnext(scan));

		systable_endscan(scan);

		if (!collides)
		{
			/*
			 * Ok, found an unused roident, insert the new row and do a CCI,
			 * so our callers can look it up if they want to.
			 */
			memset(&nulls, 0, sizeof(nulls));

			values[Anum_pg_replication_origin_roident - 1] = ObjectIdGetDatum(roident);
			values[Anum_pg_replication_origin_roname - 1] = roname_d;

			tuple = heap_form_tuple(RelationGetDescr(rel), values, nulls);
			CatalogTupleInsert(rel, tuple);
			CommandCounterIncrement();
			break;
		}
	}

	/* now release lock again,	*/
	table_close(rel, ExclusiveLock);

	if (tuple == NULL)
		ereport(ERROR,
				(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
				 errmsg("could not find free replication origin OID")));

	heap_freetuple(tuple);
	return roident;
}