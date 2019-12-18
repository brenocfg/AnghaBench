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
struct TYPE_12__ {scalar_t__ action; int /*<<< orphan*/  extname; int /*<<< orphan*/  object; int /*<<< orphan*/  objtype; } ;
struct TYPE_11__ {scalar_t__ classId; scalar_t__ objectId; scalar_t__ objectSubId; } ;
typedef  int /*<<< orphan*/ * Relation ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__ AlterExtensionContentsStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ACLCHECK_NOT_OWNER ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DEPENDENCY_EXTENSION ; 
 int /*<<< orphan*/  ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ ExtensionRelationId ; 
 int /*<<< orphan*/  GetUserId () ; 
 int /*<<< orphan*/  InvokeObjectPostAlterHook (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ NamespaceRelationId ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_EXTENSION ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 scalar_t__ RelationRelationId ; 
 int /*<<< orphan*/  ShareUpdateExclusiveLock ; 
 int /*<<< orphan*/  aclcheck_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_object_ownership (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int deleteDependencyRecordsForClass (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extension_config_remove (scalar_t__,scalar_t__) ; 
 scalar_t__ getExtensionOfObject (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  getObjectDescription (TYPE_1__*) ; 
 int /*<<< orphan*/  get_extension_name (scalar_t__) ; 
 scalar_t__ get_extension_oid (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_extension_schema (scalar_t__) ; 
 int /*<<< orphan*/  get_namespace_name (scalar_t__) ; 
 TYPE_1__ get_object_address (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pg_extension_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  recordExtObjInitPriv (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  relation_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  removeExtObjInitPriv (scalar_t__,scalar_t__) ; 

ObjectAddress
ExecAlterExtensionContentsStmt(AlterExtensionContentsStmt *stmt,
							   ObjectAddress *objAddr)
{
	ObjectAddress extension;
	ObjectAddress object;
	Relation	relation;
	Oid			oldExtension;

	extension.classId = ExtensionRelationId;
	extension.objectId = get_extension_oid(stmt->extname, false);
	extension.objectSubId = 0;

	/* Permission check: must own extension */
	if (!pg_extension_ownercheck(extension.objectId, GetUserId()))
		aclcheck_error(ACLCHECK_NOT_OWNER, OBJECT_EXTENSION,
					   stmt->extname);

	/*
	 * Translate the parser representation that identifies the object into an
	 * ObjectAddress.  get_object_address() will throw an error if the object
	 * does not exist, and will also acquire a lock on the object to guard
	 * against concurrent DROP and ALTER EXTENSION ADD/DROP operations.
	 */
	object = get_object_address(stmt->objtype, stmt->object,
								&relation, ShareUpdateExclusiveLock, false);

	Assert(object.objectSubId == 0);
	if (objAddr)
		*objAddr = object;

	/* Permission check: must own target object, too */
	check_object_ownership(GetUserId(), stmt->objtype, object,
						   stmt->object, relation);

	/*
	 * Check existing extension membership.
	 */
	oldExtension = getExtensionOfObject(object.classId, object.objectId);

	if (stmt->action > 0)
	{
		/*
		 * ADD, so complain if object is already attached to some extension.
		 */
		if (OidIsValid(oldExtension))
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("%s is already a member of extension \"%s\"",
							getObjectDescription(&object),
							get_extension_name(oldExtension))));

		/*
		 * Prevent a schema from being added to an extension if the schema
		 * contains the extension.  That would create a dependency loop.
		 */
		if (object.classId == NamespaceRelationId &&
			object.objectId == get_extension_schema(extension.objectId))
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("cannot add schema \"%s\" to extension \"%s\" "
							"because the schema contains the extension",
							get_namespace_name(object.objectId),
							stmt->extname)));

		/*
		 * OK, add the dependency.
		 */
		recordDependencyOn(&object, &extension, DEPENDENCY_EXTENSION);

		/*
		 * Also record the initial ACL on the object, if any.
		 *
		 * Note that this will handle the object's ACLs, as well as any ACLs
		 * on object subIds.  (In other words, when the object is a table,
		 * this will record the table's ACL and the ACLs for the columns on
		 * the table, if any).
		 */
		recordExtObjInitPriv(object.objectId, object.classId);
	}
	else
	{
		/*
		 * DROP, so complain if it's not a member.
		 */
		if (oldExtension != extension.objectId)
			ereport(ERROR,
					(errcode(ERRCODE_OBJECT_NOT_IN_PREREQUISITE_STATE),
					 errmsg("%s is not a member of extension \"%s\"",
							getObjectDescription(&object),
							stmt->extname)));

		/*
		 * OK, drop the dependency.
		 */
		if (deleteDependencyRecordsForClass(object.classId, object.objectId,
											ExtensionRelationId,
											DEPENDENCY_EXTENSION) != 1)
			elog(ERROR, "unexpected number of extension dependency records");

		/*
		 * If it's a relation, it might have an entry in the extension's
		 * extconfig array, which we must remove.
		 */
		if (object.classId == RelationRelationId)
			extension_config_remove(extension.objectId, object.objectId);

		/*
		 * Remove all the initial ACLs, if any.
		 *
		 * Note that this will remove the object's ACLs, as well as any ACLs
		 * on object subIds.  (In other words, when the object is a table,
		 * this will remove the table's ACL and the ACLs for the columns on
		 * the table, if any).
		 */
		removeExtObjInitPriv(object.objectId, object.classId);
	}

	InvokeObjectPostAlterHook(ExtensionRelationId, extension.objectId, 0);

	/*
	 * If get_object_address() opened the relation for us, we close it to keep
	 * the reference count correct - but we retain any locks acquired by
	 * get_object_address() until commit time, to guard against concurrent
	 * activity.
	 */
	if (relation != NULL)
		relation_close(relation, NoLock);

	return extension;
}