#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ relchecks; } ;
struct TYPE_12__ {scalar_t__ contype; int /*<<< orphan*/  contypid; int /*<<< orphan*/  conrelid; } ;
struct TYPE_11__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_constraint ;
typedef  TYPE_3__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 scalar_t__ CONSTRAINT_CHECK ; 
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/  CatalogTupleDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationGetRelationName (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ReleaseSysCache (TYPE_1__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RemoveConstraintById(Oid conId)
{
	Relation	conDesc;
	HeapTuple	tup;
	Form_pg_constraint con;

	conDesc = table_open(ConstraintRelationId, RowExclusiveLock);

	tup = SearchSysCache1(CONSTROID, ObjectIdGetDatum(conId));
	if (!HeapTupleIsValid(tup)) /* should not happen */
		elog(ERROR, "cache lookup failed for constraint %u", conId);
	con = (Form_pg_constraint) GETSTRUCT(tup);

	/*
	 * Special processing depending on what the constraint is for.
	 */
	if (OidIsValid(con->conrelid))
	{
		Relation	rel;

		/*
		 * If the constraint is for a relation, open and exclusive-lock the
		 * relation it's for.
		 */
		rel = table_open(con->conrelid, AccessExclusiveLock);

		/*
		 * We need to update the relchecks count if it is a check constraint
		 * being dropped.  This update will force backends to rebuild relcache
		 * entries when we commit.
		 */
		if (con->contype == CONSTRAINT_CHECK)
		{
			Relation	pgrel;
			HeapTuple	relTup;
			Form_pg_class classForm;

			pgrel = table_open(RelationRelationId, RowExclusiveLock);
			relTup = SearchSysCacheCopy1(RELOID,
										 ObjectIdGetDatum(con->conrelid));
			if (!HeapTupleIsValid(relTup))
				elog(ERROR, "cache lookup failed for relation %u",
					 con->conrelid);
			classForm = (Form_pg_class) GETSTRUCT(relTup);

			if (classForm->relchecks == 0)	/* should not happen */
				elog(ERROR, "relation \"%s\" has relchecks = 0",
					 RelationGetRelationName(rel));
			classForm->relchecks--;

			CatalogTupleUpdate(pgrel, &relTup->t_self, relTup);

			heap_freetuple(relTup);

			table_close(pgrel, RowExclusiveLock);
		}

		/* Keep lock on constraint's rel until end of xact */
		table_close(rel, NoLock);
	}
	else if (OidIsValid(con->contypid))
	{
		/*
		 * XXX for now, do nothing special when dropping a domain constraint
		 *
		 * Probably there should be some form of locking on the domain type,
		 * but we have no such concept at the moment.
		 */
	}
	else
		elog(ERROR, "constraint %u is not of a known type", conId);

	/* Fry the constraint itself */
	CatalogTupleDelete(conDesc, &tup->t_self);

	/* Clean up */
	ReleaseSysCache(tup);
	table_close(conDesc, RowExclusiveLock);
}