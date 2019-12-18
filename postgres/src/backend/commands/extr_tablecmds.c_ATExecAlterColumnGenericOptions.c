#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  repl_val ;
typedef  int /*<<< orphan*/  repl_repl ;
typedef  int /*<<< orphan*/  repl_null ;
struct TYPE_31__ {int /*<<< orphan*/  fdwvalidator; } ;
struct TYPE_30__ {int /*<<< orphan*/  fdwid; } ;
struct TYPE_29__ {scalar_t__ attnum; } ;
struct TYPE_28__ {int /*<<< orphan*/  ftserver; } ;
struct TYPE_27__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_26__ {int /*<<< orphan*/  rd_id; } ;
typedef  TYPE_1__* Relation ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_foreign_table ;
typedef  TYPE_4__* Form_pg_attribute ;
typedef  TYPE_5__ ForeignServer ;
typedef  TYPE_6__ ForeignDataWrapper ;
typedef  int Datum ;
typedef  scalar_t__ AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNAME ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int Anum_pg_attribute_attfdwoptions ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_1__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DatumGetPointer (int) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  FOREIGNTABLEREL ; 
 int /*<<< orphan*/  ForeignTableRelationId ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 TYPE_6__* GetForeignDataWrapper (int /*<<< orphan*/ ) ; 
 TYPE_5__* GetForeignServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 int /*<<< orphan*/  InvalidObjectAddress ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * NIL ; 
 int Natts_pg_attribute ; 
 int /*<<< orphan*/  ObjectAddressSubSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int PointerGetDatum (int /*<<< orphan*/ *) ; 
 scalar_t__ PointerIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (TYPE_1__*) ; 
 char const* RelationGetRelationName (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_1__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_2__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* SearchSysCacheAttName (int /*<<< orphan*/ ,char const*) ; 
 int SysCacheGetAttr (int /*<<< orphan*/ ,TYPE_2__*,int,int*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 TYPE_2__* heap_modify_tuple (TYPE_2__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  table_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int transformGenericOptions (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
ATExecAlterColumnGenericOptions(Relation rel,
								const char *colName,
								List *options,
								LOCKMODE lockmode)
{
	Relation	ftrel;
	Relation	attrel;
	ForeignServer *server;
	ForeignDataWrapper *fdw;
	HeapTuple	tuple;
	HeapTuple	newtuple;
	bool		isnull;
	Datum		repl_val[Natts_pg_attribute];
	bool		repl_null[Natts_pg_attribute];
	bool		repl_repl[Natts_pg_attribute];
	Datum		datum;
	Form_pg_foreign_table fttableform;
	Form_pg_attribute atttableform;
	AttrNumber	attnum;
	ObjectAddress address;

	if (options == NIL)
		return InvalidObjectAddress;

	/* First, determine FDW validator associated to the foreign table. */
	ftrel = table_open(ForeignTableRelationId, AccessShareLock);
	tuple = SearchSysCache1(FOREIGNTABLEREL, rel->rd_id);
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("foreign table \"%s\" does not exist",
						RelationGetRelationName(rel))));
	fttableform = (Form_pg_foreign_table) GETSTRUCT(tuple);
	server = GetForeignServer(fttableform->ftserver);
	fdw = GetForeignDataWrapper(server->fdwid);

	table_close(ftrel, AccessShareLock);
	ReleaseSysCache(tuple);

	attrel = table_open(AttributeRelationId, RowExclusiveLock);
	tuple = SearchSysCacheAttName(RelationGetRelid(rel), colName);
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_COLUMN),
				 errmsg("column \"%s\" of relation \"%s\" does not exist",
						colName, RelationGetRelationName(rel))));

	/* Prevent them from altering a system attribute */
	atttableform = (Form_pg_attribute) GETSTRUCT(tuple);
	attnum = atttableform->attnum;
	if (attnum <= 0)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot alter system column \"%s\"", colName)));


	/* Initialize buffers for new tuple values */
	memset(repl_val, 0, sizeof(repl_val));
	memset(repl_null, false, sizeof(repl_null));
	memset(repl_repl, false, sizeof(repl_repl));

	/* Extract the current options */
	datum = SysCacheGetAttr(ATTNAME,
							tuple,
							Anum_pg_attribute_attfdwoptions,
							&isnull);
	if (isnull)
		datum = PointerGetDatum(NULL);

	/* Transform the options */
	datum = transformGenericOptions(AttributeRelationId,
									datum,
									options,
									fdw->fdwvalidator);

	if (PointerIsValid(DatumGetPointer(datum)))
		repl_val[Anum_pg_attribute_attfdwoptions - 1] = datum;
	else
		repl_null[Anum_pg_attribute_attfdwoptions - 1] = true;

	repl_repl[Anum_pg_attribute_attfdwoptions - 1] = true;

	/* Everything looks good - update the tuple */

	newtuple = heap_modify_tuple(tuple, RelationGetDescr(attrel),
								 repl_val, repl_null, repl_repl);

	CatalogTupleUpdate(attrel, &newtuple->t_self, newtuple);

	InvokeObjectPostAlterHook(RelationRelationId,
							  RelationGetRelid(rel),
							  atttableform->attnum);
	ObjectAddressSubSet(address, RelationRelationId,
						RelationGetRelid(rel), attnum);

	ReleaseSysCache(tuple);

	table_close(attrel, RowExclusiveLock);

	heap_freetuple(newtuple);

	return address;
}