#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int verify_new_notnull; } ;
struct TYPE_11__ {scalar_t__ attnum; int attnotnull; } ;
struct TYPE_10__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_attribute ;
typedef  scalar_t__ AttrNumber ;
typedef  TYPE_3__ AlteredTableInfo ;

/* Variables and functions */
 int /*<<< orphan*/  AttributeRelationId ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_COLUMN ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvalidObjectAddress ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  NotNullImpliedByRelConstraints (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ObjectAddressSubSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopyAttName (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ObjectAddress
ATExecSetNotNull(AlteredTableInfo *tab, Relation rel,
				 const char *colName, LOCKMODE lockmode)
{
	HeapTuple	tuple;
	AttrNumber	attnum;
	Relation	attr_rel;
	ObjectAddress address;

	/*
	 * lookup the attribute
	 */
	attr_rel = table_open(AttributeRelationId, RowExclusiveLock);

	tuple = SearchSysCacheCopyAttName(RelationGetRelid(rel), colName);

	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_COLUMN),
				 errmsg("column \"%s\" of relation \"%s\" does not exist",
						colName, RelationGetRelationName(rel))));

	attnum = ((Form_pg_attribute) GETSTRUCT(tuple))->attnum;

	/* Prevent them from altering a system attribute */
	if (attnum <= 0)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot alter system column \"%s\"",
						colName)));

	/*
	 * Okay, actually perform the catalog change ... if needed
	 */
	if (!((Form_pg_attribute) GETSTRUCT(tuple))->attnotnull)
	{
		((Form_pg_attribute) GETSTRUCT(tuple))->attnotnull = true;

		CatalogTupleUpdate(attr_rel, &tuple->t_self, tuple);

		/*
		 * Ordinarily phase 3 must ensure that no NULLs exist in columns that
		 * are set NOT NULL; however, if we can find a constraint which proves
		 * this then we can skip that.  We needn't bother looking if we've
		 * already found that we must verify some other NOT NULL constraint.
		 */
		if (!tab->verify_new_notnull &&
			!NotNullImpliedByRelConstraints(rel, (Form_pg_attribute) GETSTRUCT(tuple)))
		{
			/* Tell Phase 3 it needs to test the constraint */
			tab->verify_new_notnull = true;
		}

		ObjectAddressSubSet(address, RelationRelationId,
							RelationGetRelid(rel), attnum);
	}
	else
		address = InvalidObjectAddress;

	InvokeObjectPostAlterHook(RelationRelationId,
							  RelationGetRelid(rel), attnum);

	table_close(attr_rel, RowExclusiveLock);

	return address;
}