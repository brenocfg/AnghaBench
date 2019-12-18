#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  repl_val ;
typedef  int /*<<< orphan*/  repl_repl ;
typedef  int /*<<< orphan*/  repl_null ;
struct TYPE_12__ {scalar_t__ atthasmissing; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  int Datum ;

/* Variables and functions */
 int /*<<< orphan*/  ATTNUM ; 
 int Anum_pg_attribute_atthasmissing ; 
 int Anum_pg_attribute_attmissingval ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int BoolGetDatum (int) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  Int16GetDatum (int) ; 
 int Natts_pg_attribute ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetDescr (int /*<<< orphan*/ ) ; 
 int RelationGetNumberOfAttributes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 TYPE_1__* heap_modify_tuple (TYPE_1__*,int /*<<< orphan*/ ,int*,int*,int*) ; 
 int /*<<< orphan*/  memset (int*,int,int) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RelationClearMissing(Relation rel)
{
	Relation	attr_rel;
	Oid			relid = RelationGetRelid(rel);
	int			natts = RelationGetNumberOfAttributes(rel);
	int			attnum;
	Datum		repl_val[Natts_pg_attribute];
	bool		repl_null[Natts_pg_attribute];
	bool		repl_repl[Natts_pg_attribute];
	Form_pg_attribute attrtuple;
	HeapTuple	tuple,
				newtuple;

	memset(repl_val, 0, sizeof(repl_val));
	memset(repl_null, false, sizeof(repl_null));
	memset(repl_repl, false, sizeof(repl_repl));

	repl_val[Anum_pg_attribute_atthasmissing - 1] = BoolGetDatum(false);
	repl_null[Anum_pg_attribute_attmissingval - 1] = true;

	repl_repl[Anum_pg_attribute_atthasmissing - 1] = true;
	repl_repl[Anum_pg_attribute_attmissingval - 1] = true;


	/* Get a lock on pg_attribute */
	attr_rel = table_open(AttributeRelationId, RowExclusiveLock);

	/* process each non-system attribute, including any dropped columns */
	for (attnum = 1; attnum <= natts; attnum++)
	{
		tuple = SearchSysCache2(ATTNUM,
								ObjectIdGetDatum(relid),
								Int16GetDatum(attnum));
		if (!HeapTupleIsValid(tuple))	/* shouldn't happen */
			elog(ERROR, "cache lookup failed for attribute %d of relation %u",
				 attnum, relid);

		attrtuple = (Form_pg_attribute) GETSTRUCT(tuple);

		/* ignore any where atthasmissing is not true */
		if (attrtuple->atthasmissing)
		{
			newtuple = heap_modify_tuple(tuple, RelationGetDescr(attr_rel),
										 repl_val, repl_null, repl_repl);

			CatalogTupleUpdate(attr_rel, &newtuple->t_self, newtuple);

			heap_freetuple(newtuple);
		}

		ReleaseSysCache(tuple);
	}

	/*
	 * Our update of the pg_attribute rows will force a relcache rebuild, so
	 * there's nothing else to do here.
	 */
	table_close(attr_rel, RowExclusiveLock);
}