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
struct TYPE_9__ {int /*<<< orphan*/  conname; int /*<<< orphan*/  contypid; int /*<<< orphan*/  conrelid; } ;
struct TYPE_8__ {int /*<<< orphan*/  t_self; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__* HeapTuple ;
typedef  TYPE_2__* Form_pg_constraint ;

/* Variables and functions */
 int /*<<< orphan*/  CONSTRAINT_DOMAIN ; 
 int /*<<< orphan*/  CONSTRAINT_RELATION ; 
 int /*<<< orphan*/  CONSTROID ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ ConstraintNameIsUsed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  ConstraintRelationId ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_1__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_1__*) ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_1__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format_type_be (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_1__*) ; 
 int /*<<< orphan*/  namestrcpy (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
RenameConstraintById(Oid conId, const char *newname)
{
	Relation	conDesc;
	HeapTuple	tuple;
	Form_pg_constraint con;

	conDesc = table_open(ConstraintRelationId, RowExclusiveLock);

	tuple = SearchSysCacheCopy1(CONSTROID, ObjectIdGetDatum(conId));
	if (!HeapTupleIsValid(tuple))
		elog(ERROR, "cache lookup failed for constraint %u", conId);
	con = (Form_pg_constraint) GETSTRUCT(tuple);

	/*
	 * For user-friendliness, check whether the name is already in use.
	 */
	if (OidIsValid(con->conrelid) &&
		ConstraintNameIsUsed(CONSTRAINT_RELATION,
							 con->conrelid,
							 newname))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("constraint \"%s\" for relation \"%s\" already exists",
						newname, get_rel_name(con->conrelid))));
	if (OidIsValid(con->contypid) &&
		ConstraintNameIsUsed(CONSTRAINT_DOMAIN,
							 con->contypid,
							 newname))
		ereport(ERROR,
				(errcode(ERRCODE_DUPLICATE_OBJECT),
				 errmsg("constraint \"%s\" for domain %s already exists",
						newname, format_type_be(con->contypid))));

	/* OK, do the rename --- tuple is a copy, so OK to scribble on it */
	namestrcpy(&(con->conname), newname);

	CatalogTupleUpdate(conDesc, &tuple->t_self, tuple);

	InvokeObjectPostAlterHook(ConstraintRelationId, conId, 0);

	heap_freetuple(tuple);
	table_close(conDesc, RowExclusiveLock);
}