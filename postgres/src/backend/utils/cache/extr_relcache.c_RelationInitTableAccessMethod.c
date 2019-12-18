#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {void* amhandler; } ;
struct TYPE_8__ {void* rd_amhandler; TYPE_1__* rd_rel; } ;
struct TYPE_7__ {scalar_t__ relkind; scalar_t__ relam; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_3__* Form_pg_am ;

/* Variables and functions */
 int /*<<< orphan*/  AMOID ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 void* HEAP_TABLE_AM_HANDLER_OID ; 
 scalar_t__ HEAP_TABLE_AM_OID ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InitTableAmRoutine (TYPE_2__*) ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ IsCatalogRelation (TYPE_2__*) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 

void
RelationInitTableAccessMethod(Relation relation)
{
	HeapTuple	tuple;
	Form_pg_am	aform;

	if (relation->rd_rel->relkind == RELKIND_SEQUENCE)
	{
		/*
		 * Sequences are currently accessed like heap tables, but it doesn't
		 * seem prudent to show that in the catalog. So just overwrite it
		 * here.
		 */
		relation->rd_amhandler = HEAP_TABLE_AM_HANDLER_OID;
	}
	else if (IsCatalogRelation(relation))
	{
		/*
		 * Avoid doing a syscache lookup for catalog tables.
		 */
		Assert(relation->rd_rel->relam == HEAP_TABLE_AM_OID);
		relation->rd_amhandler = HEAP_TABLE_AM_HANDLER_OID;
	}
	else
	{
		/*
		 * Look up the table access method, save the OID of its handler
		 * function.
		 */
		Assert(relation->rd_rel->relam != InvalidOid);
		tuple = SearchSysCache1(AMOID,
								ObjectIdGetDatum(relation->rd_rel->relam));
		if (!HeapTupleIsValid(tuple))
			elog(ERROR, "cache lookup failed for access method %u",
				 relation->rd_rel->relam);
		aform = (Form_pg_am) GETSTRUCT(tuple);
		relation->rd_amhandler = aform->amhandler;
		ReleaseSysCache(tuple);
	}

	/*
	 * Now we can fetch the table AM's API struct
	 */
	InitTableAmRoutine(relation);
}