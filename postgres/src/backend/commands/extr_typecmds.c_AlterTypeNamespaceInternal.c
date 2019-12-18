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
struct TYPE_13__ {scalar_t__ typtype; void* typrelid; void* typnamespace; int /*<<< orphan*/  typname; void* typarray; } ;
struct TYPE_12__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_11__ {scalar_t__ objectSubId; void* objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_type ;

/* Variables and functions */
 int /*<<< orphan*/  AlterConstraintNamespaces (void*,void*,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AlterRelationNamespaceInternal (int /*<<< orphan*/ ,void*,void*,void*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  CheckSetNamespace (void*,void*) ; 
 int /*<<< orphan*/  ERRCODE_DUPLICATE_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  HeapTupleIsValid (TYPE_2__*) ; 
 void* InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NameGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (void*) ; 
 scalar_t__ OidIsValid (void*) ; 
 scalar_t__ RELKIND_COMPOSITE_TYPE ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_2__* SearchSysCacheCopy1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SearchSysCacheExists2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPENAMENSP ; 
 int /*<<< orphan*/  TYPEOID ; 
 scalar_t__ TYPTYPE_COMPOSITE ; 
 scalar_t__ TYPTYPE_DOMAIN ; 
 int /*<<< orphan*/  TypeRelationId ; 
 int /*<<< orphan*/  add_exact_object_address (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int changeDependencyFor (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,void*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,void*,...) ; 
 void* format_type_be (void*) ; 
 int /*<<< orphan*/  get_namespace_name (void*) ; 
 scalar_t__ get_rel_relkind (void*) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_2__*) ; 
 scalar_t__ object_address_present (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

Oid
AlterTypeNamespaceInternal(Oid typeOid, Oid nspOid,
						   bool isImplicitArray,
						   bool errorOnTableType,
						   ObjectAddresses *objsMoved)
{
	Relation	rel;
	HeapTuple	tup;
	Form_pg_type typform;
	Oid			oldNspOid;
	Oid			arrayOid;
	bool		isCompositeType;
	ObjectAddress thisobj;

	/*
	 * Make sure we haven't moved this object previously.
	 */
	thisobj.classId = TypeRelationId;
	thisobj.objectId = typeOid;
	thisobj.objectSubId = 0;

	if (object_address_present(&thisobj, objsMoved))
		return InvalidOid;

	rel = table_open(TypeRelationId, RowExclusiveLock);

	tup = SearchSysCacheCopy1(TYPEOID, ObjectIdGetDatum(typeOid));
	if (!HeapTupleIsValid(tup))
		elog(ERROR, "cache lookup failed for type %u", typeOid);
	typform = (Form_pg_type) GETSTRUCT(tup);

	oldNspOid = typform->typnamespace;
	arrayOid = typform->typarray;

	/* If the type is already there, we scan skip these next few checks. */
	if (oldNspOid != nspOid)
	{
		/* common checks on switching namespaces */
		CheckSetNamespace(oldNspOid, nspOid);

		/* check for duplicate name (more friendly than unique-index failure) */
		if (SearchSysCacheExists2(TYPENAMENSP,
								  NameGetDatum(&typform->typname),
								  ObjectIdGetDatum(nspOid)))
			ereport(ERROR,
					(errcode(ERRCODE_DUPLICATE_OBJECT),
					 errmsg("type \"%s\" already exists in schema \"%s\"",
							NameStr(typform->typname),
							get_namespace_name(nspOid))));
	}

	/* Detect whether type is a composite type (but not a table rowtype) */
	isCompositeType =
		(typform->typtype == TYPTYPE_COMPOSITE &&
		 get_rel_relkind(typform->typrelid) == RELKIND_COMPOSITE_TYPE);

	/* Enforce not-table-type if requested */
	if (typform->typtype == TYPTYPE_COMPOSITE && !isCompositeType &&
		errorOnTableType)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("%s is a table's row type",
						format_type_be(typeOid)),
				 errhint("Use ALTER TABLE instead.")));

	if (oldNspOid != nspOid)
	{
		/* OK, modify the pg_type row */

		/* tup is a copy, so we can scribble directly on it */
		typform->typnamespace = nspOid;

		CatalogTupleUpdate(rel, &tup->t_self, tup);
	}

	/*
	 * Composite types have pg_class entries.
	 *
	 * We need to modify the pg_class tuple as well to reflect the change of
	 * schema.
	 */
	if (isCompositeType)
	{
		Relation	classRel;

		classRel = table_open(RelationRelationId, RowExclusiveLock);

		AlterRelationNamespaceInternal(classRel, typform->typrelid,
									   oldNspOid, nspOid,
									   false, objsMoved);

		table_close(classRel, RowExclusiveLock);

		/*
		 * Check for constraints associated with the composite type (we don't
		 * currently support this, but probably will someday).
		 */
		AlterConstraintNamespaces(typform->typrelid, oldNspOid,
								  nspOid, false, objsMoved);
	}
	else
	{
		/* If it's a domain, it might have constraints */
		if (typform->typtype == TYPTYPE_DOMAIN)
			AlterConstraintNamespaces(typeOid, oldNspOid, nspOid, true,
									  objsMoved);
	}

	/*
	 * Update dependency on schema, if any --- a table rowtype has not got
	 * one, and neither does an implicit array.
	 */
	if (oldNspOid != nspOid &&
		(isCompositeType || typform->typtype != TYPTYPE_COMPOSITE) &&
		!isImplicitArray)
		if (changeDependencyFor(TypeRelationId, typeOid,
								NamespaceRelationId, oldNspOid, nspOid) != 1)
			elog(ERROR, "failed to change schema dependency for type %s",
				 format_type_be(typeOid));

	InvokeObjectPostAlterHook(TypeRelationId, typeOid, 0);

	heap_freetuple(tup);

	table_close(rel, RowExclusiveLock);

	add_exact_object_address(&thisobj, objsMoved);

	/* Recursively alter the associated array type, if any */
	if (OidIsValid(arrayOid))
		AlterTypeNamespaceInternal(arrayOid, nspOid, true, true, objsMoved);

	return oldNspOid;
}