#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ deptype; scalar_t__ objsubid; int /*<<< orphan*/  objid; int /*<<< orphan*/  classid; } ;
struct TYPE_17__ {scalar_t__ extnamespace; int /*<<< orphan*/  extname; int /*<<< orphan*/  extrelocatable; } ;
struct TYPE_16__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_15__ {scalar_t__ objectSubId; int /*<<< orphan*/  objectId; int /*<<< orphan*/  classId; } ;
typedef  int /*<<< orphan*/  SysScanDesc ;
typedef  int /*<<< orphan*/  ScanKeyData ;
typedef  int /*<<< orphan*/  Relation ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__* HeapTuple ;
typedef  TYPE_3__* Form_pg_extension ;
typedef  TYPE_4__* Form_pg_depend ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_NOT_OWNER ; 
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  AccessShareLock ; 
 scalar_t__ AlterObjectNamespace_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Anum_pg_depend_refclassid ; 
 int /*<<< orphan*/  Anum_pg_depend_refobjid ; 
 int /*<<< orphan*/  Anum_pg_extension_oid ; 
 int /*<<< orphan*/  BTEqualStrategyNumber ; 
 int /*<<< orphan*/  CatalogTupleUpdate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ DEPENDENCY_EXTENSION ; 
 int /*<<< orphan*/  DependReferenceIndexId ; 
 scalar_t__ DependRelationId ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExtensionOidIndexId ; 
 scalar_t__ ExtensionRelationId ; 
 int /*<<< orphan*/  F_OIDEQ ; 
 scalar_t__ GETSTRUCT (TYPE_2__*) ; 
 int /*<<< orphan*/  GetUserId () ; 
 scalar_t__ HeapTupleIsValid (TYPE_2__*) ; 
 TYPE_1__ InvalidObjectAddress ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ LookupCreationNamespace (char const*) ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  OBJECT_EXTENSION ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 int /*<<< orphan*/  ObjectAddressSet (TYPE_1__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ObjectIdGetDatum (scalar_t__) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  ScanKeyInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  changeDependencyFor (scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*,...) ; 
 scalar_t__ getExtensionOfObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  getObjectDescription (TYPE_1__*) ; 
 scalar_t__ get_extension_oid (char const*,int) ; 
 int /*<<< orphan*/  get_namespace_name (scalar_t__) ; 
 TYPE_2__* heap_copytuple (TYPE_2__*) ; 
 int /*<<< orphan*/ * new_object_addresses () ; 
 int /*<<< orphan*/  pg_extension_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_namespace_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  systable_beginscan (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  systable_endscan (int /*<<< orphan*/ ) ; 
 TYPE_2__* systable_getnext (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (scalar_t__,int /*<<< orphan*/ ) ; 

ObjectAddress
AlterExtensionNamespace(const char *extensionName, const char *newschema, Oid *oldschema)
{
	Oid			extensionOid;
	Oid			nspOid;
	Oid			oldNspOid = InvalidOid;
	AclResult	aclresult;
	Relation	extRel;
	ScanKeyData key[2];
	SysScanDesc extScan;
	HeapTuple	extTup;
	Form_pg_extension extForm;
	Relation	depRel;
	SysScanDesc depScan;
	HeapTuple	depTup;
	ObjectAddresses *objsMoved;
	ObjectAddress extAddr;

	extensionOid = get_extension_oid(extensionName, false);

	nspOid = LookupCreationNamespace(newschema);

	/*
	 * Permission check: must own extension.  Note that we don't bother to
	 * check ownership of the individual member objects ...
	 */
	if (!pg_extension_ownercheck(extensionOid, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_EXTENSION,
					   extensionName);

	/* Permission check: must have creation rights in target namespace */
	aclresult = pg_namespace_aclcheck(nspOid, GetUserId(), ACL_CREATE);
	if (aclresult != ACLCHECK_OK)
		aclcheck_error(aclresult, OBJECT_SCHEMA, newschema);

	/*
	 * If the schema is currently a member of the extension, disallow moving
	 * the extension into the schema.  That would create a dependency loop.
	 */
	if (getExtensionOfObject(NamespaceRelationId, nspOid) == extensionOid)
		ereport(ERROR,
				(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
				 errmsg("cannot move extension \"%s\" into schema \"%s\" "
						"because the extension contains the schema",
						extensionName, newschema)));

	/* Locate the pg_extension tuple */
	extRel = table_open(ExtensionRelationId, RowExclusiveLock);

	ScanKeyInit(&key[0],
				Anum_pg_extension_oid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(extensionOid));

	extScan = systable_beginscan(extRel, ExtensionOidIndexId, true,
								 NULL, 1, key);

	extTup = systable_getnext(extScan);

	if (!HeapTupleIsValid(extTup))	/* should not happen */
		elog(ERROR, "could not find tuple for extension %u",
			 extensionOid);

	/* Copy tuple so we can modify it below */
	extTup = heap_copytuple(extTup);
	extForm = (Form_pg_extension) GETSTRUCT(extTup);

	systable_endscan(extScan);

	/*
	 * If the extension is already in the target schema, just silently do
	 * nothing.
	 */
	if (extForm->extnamespace == nspOid)
	{
		table_close(extRel, RowExclusiveLock);
		return InvalidObjectAddress;
	}

	/* Check extension is supposed to be relocatable */
	if (!extForm->extrelocatable)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("extension \"%s\" does not support SET SCHEMA",
						NameStr(extForm->extname))));

	objsMoved = new_object_addresses();

	/*
	 * Scan pg_depend to find objects that depend directly on the extension,
	 * and alter each one's schema.
	 */
	depRel = table_open(DependRelationId, AccessShareLock);

	ScanKeyInit(&key[0],
				Anum_pg_depend_refclassid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(ExtensionRelationId));
	ScanKeyInit(&key[1],
				Anum_pg_depend_refobjid,
				BTEqualStrategyNumber, F_OIDEQ,
				ObjectIdGetDatum(extensionOid));

	depScan = systable_beginscan(depRel, DependReferenceIndexId, true,
								 NULL, 2, key);

	while (HeapTupleIsValid(depTup = systable_getnext(depScan)))
	{
		Form_pg_depend pg_depend = (Form_pg_depend) GETSTRUCT(depTup);
		ObjectAddress dep;
		Oid			dep_oldNspOid;

		/*
		 * Ignore non-membership dependencies.  (Currently, the only other
		 * case we could see here is a normal dependency from another
		 * extension.)
		 */
		if (pg_depend->deptype != DEPENDENCY_EXTENSION)
			continue;

		dep.classId = pg_depend->classid;
		dep.objectId = pg_depend->objid;
		dep.objectSubId = pg_depend->objsubid;

		if (dep.objectSubId != 0)	/* should not happen */
			elog(ERROR, "extension should not have a sub-object dependency");

		/* Relocate the object */
		dep_oldNspOid = AlterObjectNamespace_oid(dep.classId,
												 dep.objectId,
												 nspOid,
												 objsMoved);

		/*
		 * Remember previous namespace of first object that has one
		 */
		if (oldNspOid == InvalidOid && dep_oldNspOid != InvalidOid)
			oldNspOid = dep_oldNspOid;

		/*
		 * If not all the objects had the same old namespace (ignoring any
		 * that are not in namespaces), complain.
		 */
		if (dep_oldNspOid != InvalidOid && dep_oldNspOid != oldNspOid)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("extension \"%s\" does not support SET SCHEMA",
							NameStr(extForm->extname)),
					 errdetail("%s is not in the extension's schema \"%s\"",
							   getObjectDescription(&dep),
							   get_namespace_name(oldNspOid))));
	}

	/* report old schema, if caller wants it */
	if (oldschema)
		*oldschema = oldNspOid;

	systable_endscan(depScan);

	relation_close(depRel, AccessShareLock);

	/* Now adjust pg_extension.extnamespace */
	extForm->extnamespace = nspOid;

	CatalogTupleUpdate(extRel, &extTup->t_self, extTup);

	table_close(extRel, RowExclusiveLock);

	/* update dependencies to point to the new schema */
	changeDependencyFor(ExtensionRelationId, extensionOid,
						NamespaceRelationId, oldNspOid, nspOid);

	InvokeObjectPostAlterHook(ExtensionRelationId, extensionOid, 0);

	ObjectAddressSet(extAddr, ExtensionRelationId, extensionOid);

	return extAddr;
}