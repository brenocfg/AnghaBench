#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  repl_repl ;
typedef  int /*<<< orphan*/  repl_null ;
typedef  int /*<<< orphan*/  TableScanDesc ;
struct TYPE_15__ {int /*<<< orphan*/  isReset; int /*<<< orphan*/  options; int /*<<< orphan*/  tablespacename; } ;
struct TYPE_14__ {int /*<<< orphan*/  oid; } ;
struct TYPE_13__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_tablespace ;
typedef  scalar_t__ Datum ;
typedef  TYPE_3__ AlterTableSpaceOptionsStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  Anum_pg_tablespace_spcname ; 
 int Anum_pg_tablespace_spcoptions ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CStringGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  F_NAMEEQ ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int Natts_pg_tablespace ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_TABLESPACE ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TableSpaceRelationId ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 scalar_t__ heap_getattr (TYPE_1__*,int,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  pg_tablespace_ownercheck (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_beginscan_catalog (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tablespace_reloptions (scalar_t__,int) ; 
 scalar_t__ transformRelOptions (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

Oid
AlterTableSpaceOptions(AlterTableSpaceOptionsStmt *stmt)
{
	Relation	rel;
	ScanKeyData entry[1];
	TableScanDesc scandesc;
	HeapTuple	tup;
	Oid			tablespaceoid;
	Datum		datum;
	Datum		newOptions;
	Datum		repl_val[Natts_pg_tablespace];
	bool		isnull;
	bool		repl_null[Natts_pg_tablespace];
	bool		repl_repl[Natts_pg_tablespace];
	HeapTuple	newtuple;

	/* Search pg_tablespace */
	rel = table_open(TableSpaceRelationId, RowExclusiveLock);

	ScanKeyInit(&entry[0],
				Anum_pg_tablespace_spcname,
				BTEqualStrategyNumber, F_NAMEEQ,
				CStringGetDatum(stmt->tablespacename));
	scandesc = table_beginscan_catalog(rel, 1, entry);
	tup = heap_getnext(scandesc, ForwardScanDirection);
	if (!HeapTupleIsValid(tup))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("tablespace \"%s\" does not exist",
						stmt->tablespacename)));

	tablespaceoid = ((Form_pg_tablespace) GETSTRUCT(tup))->oid;

	/* Must be owner of the existing object */
	if (!pg_tablespace_ownercheck(tablespaceoid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_TABLESPACE,
					   stmt->tablespacename);

	/* Generate new proposed spcoptions (text array) */
	datum = heap_getattr(tup, Anum_pg_tablespace_spcoptions,
						 RelationGetDescr(rel), &isnull);
	newOptions = transformRelOptions(isnull ? (Datum) 0 : datum,
									 stmt->options, NULL, NULL, false,
									 stmt->isReset);
	(void) tablespace_reloptions(newOptions, true);

	/* Build new tuple. */
	memset(repl_null, false, sizeof(repl_null));
	memset(repl_repl, false, sizeof(repl_repl));
	if (newOptions != (Datum) 0)
		repl_val[Anum_pg_tablespace_spcoptions - 1] = newOptions;
	else
		repl_null[Anum_pg_tablespace_spcoptions - 1] = true;
	repl_repl[Anum_pg_tablespace_spcoptions - 1] = true;
	newtuple = heap_modify_tuple(tup, RelationGetDescr(rel), repl_val,
								 repl_null, repl_repl);

	/* Update system catalog. */
	CatalogTupleUpdate(rel, &newtuple->t_self, newtuple);

	InvokeObjectPostAlterHook(TableSpaceRelationId, tablespaceoid, 0);

	heap_freetuple(newtuple);

	/* Conclude heap scan. */
	table_endscan(scandesc);
	table_close(rel, NoLock);

	return tablespaceoid;
}