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
struct TYPE_13__ {scalar_t__ relnamespace; int /*<<< orphan*/  relname; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_11__ {scalar_t__ objectSubId; scalar_t__ objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_class ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_TABLE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  RELOID ; 
 int /*<<< orphan*/  RelationRelationId ; 
 TYPE_2__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_exact_object_address (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int changeDependencyFor (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name (scalar_t__) ; 
 scalar_t__ get_relname_relid (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 int object_address_present (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
AlterRelationNamespaceInternal(Relation classRel, Oid relOid,
							   Oid oldNspOid, Oid newNspOid,
							   bool hasDependEntry,
							   ObjectAddresses *objsMoved)
{
	HeapTuple	classTup;
	Form_pg_class classForm;
	ObjectAddress thisobj;
	bool		already_done = false;

	classTup = SearchSysCacheCopy1(RELOID, ObjectIdGetDatum(relOid));
	if (!HeapTupleIsValid(classTup))
		elog(ERROR, "cache lookup failed for relation %u", relOid);
	classForm = (Form_pg_class) GETSTRUCT(classTup);

	Assert(classForm->relnamespace == oldNspOid);

	thisobj.classId = RelationRelationId;
	thisobj.objectId = relOid;
	thisobj.objectSubId = 0;

	/*
	 * If the object has already been moved, don't move it again.  If it's
	 * already in the right place, don't move it, but still fire the object
	 * access hook.
	 */
	already_done = object_address_present(&thisobj, objsMoved);
	if (!already_done && oldNspOid != newNspOid)
	{
		/* check for duplicate name (more friendly than unique-index failure) */
		if (get_relname_relid(NameStr(classForm->relname),
							  newNspOid) != InvalidOid)
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_TABLE),
					 errmsg("relation \"%s\" already exists in schema \"%s\"",
							NameStr(classForm->relname),
							get_namespace_name(newNspOid))));

		/* classTup is a copy, so OK to scribble on */
		classForm->relnamespace = newNspOid;

		CatalogTupleUpdate(classRel, &classTup->t_self, classTup);

		/* Update dependency on schema if caller said so */
		if (hasDependEntry &&
			changeDependencyFor(RelationRelationId,
								relOid,
								NamespaceRelationId,
								oldNspOid,
								newNspOid) != 1)
			elog(ERROR, "failed to change schema dependency for relation \"%s\"",
				 NameStr(classForm->relname));
	}
	if (!already_done)
	{
		add_exact_object_address(&thisobj, objsMoved);

		InvokeObjectPostAlterHook(RelationRelationId, relOid, 0);
	}

	heap_freetuple(classTup);
}