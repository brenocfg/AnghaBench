#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64 ;
struct TYPE_5__ {int /*<<< orphan*/  relname; int /*<<< orphan*/  schemaname; scalar_t__ catalogname; } ;
typedef  TYPE_1__ RangeVar ;
typedef  scalar_t__ Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  scalar_t__ AclResult ;

/* Variables and functions */
 scalar_t__ ACLCHECK_NOT_OWNER ; 
 scalar_t__ ACLCHECK_OK ; 
 int /*<<< orphan*/  ACL_CREATE ; 
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  Assert (scalar_t__) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GetUserId () ; 
 scalar_t__ InvalidOid ; 
 scalar_t__ IsBootstrapProcessingMode () ; 
 int /*<<< orphan*/  LockDatabaseObject (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockRelationOid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  NamespaceRelationId ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OBJECT_SCHEMA ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  RangeVarAdjustRelationPersistence (TYPE_1__*,scalar_t__) ; 
 scalar_t__ RangeVarGetCreationNamespace (TYPE_1__*) ; 
 scalar_t__ SharedInvalidMessageCounter ; 
 int /*<<< orphan*/  UnlockDatabaseObject (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockRelationOid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aclcheck_error (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_database_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_namespace_name (scalar_t__) ; 
 int /*<<< orphan*/  get_rel_relkind (scalar_t__) ; 
 int /*<<< orphan*/  get_relkind_objtype (int /*<<< orphan*/ ) ; 
 scalar_t__ get_relname_relid (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pg_class_ownercheck (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pg_namespace_aclcheck (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 

Oid
RangeVarGetAndCheckCreationNamespace(RangeVar *relation,
									 LOCKMODE lockmode,
									 Oid *existing_relation_id)
{
	uint64		inval_count;
	Oid			relid;
	Oid			oldrelid = InvalidOid;
	Oid			nspid;
	Oid			oldnspid = InvalidOid;
	bool		retry = false;

	/*
	 * We check the catalog name and then ignore it.
	 */
	if (relation->catalogname)
	{
		if (strcmp(relation->catalogname, get_database_name(MyDatabaseId)) != 0)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cross-database references are not implemented: \"%s.%s.%s\"",
							relation->catalogname, relation->schemaname,
							relation->relname)));
	}

	/*
	 * As in RangeVarGetRelidExtended(), we guard against concurrent DDL
	 * operations by tracking whether any invalidation messages are processed
	 * while we're doing the name lookups and acquiring locks.  See comments
	 * in that function for a more detailed explanation of this logic.
	 */
	for (;;)
	{
		AclResult	aclresult;

		inval_count = SharedInvalidMessageCounter;

		/* Look up creation namespace and check for existing relation. */
		nspid = RangeVarGetCreationNamespace(relation);
		Assert(OidIsValid(nspid));
		if (existing_relation_id != NULL)
			relid = get_relname_relid(relation->relname, nspid);
		else
			relid = InvalidOid;

		/*
		 * In bootstrap processing mode, we don't bother with permissions or
		 * locking.  Permissions might not be working yet, and locking is
		 * unnecessary.
		 */
		if (IsBootstrapProcessingMode())
			break;

		/* Check namespace permissions. */
		aclresult = pg_namespace_aclcheck(nspid, GetUserId(), ACL_CREATE);
		if (aclresult != ACLCHECK_OK)
			aclcheck_error(aclresult, OBJECT_SCHEMA,
						   get_namespace_name(nspid));

		if (retry)
		{
			/* If nothing changed, we're done. */
			if (relid == oldrelid && nspid == oldnspid)
				break;
			/* If creation namespace has changed, give up old lock. */
			if (nspid != oldnspid)
				UnlockDatabaseObject(NamespaceRelationId, oldnspid, 0,
									 AccessShareLock);
			/* If name points to something different, give up old lock. */
			if (relid != oldrelid && OidIsValid(oldrelid) && lockmode != NoLock)
				UnlockRelationOid(oldrelid, lockmode);
		}

		/* Lock namespace. */
		if (nspid != oldnspid)
			LockDatabaseObject(NamespaceRelationId, nspid, 0, AccessShareLock);

		/* Lock relation, if required if and we have permission. */
		if (lockmode != NoLock && OidIsValid(relid))
		{
			if (!pg_class_ownercheck(relid, GetUserId()))
				aclcheck_error(ACLCHECK_NOT_OWNER, get_relkind_objtype(get_rel_relkind(relid)),
							   relation->relname);
			if (relid != oldrelid)
				LockRelationOid(relid, lockmode);
		}

		/* If no invalidation message were processed, we're done! */
		if (inval_count == SharedInvalidMessageCounter)
			break;

		/* Something may have changed, so recheck our work. */
		retry = true;
		oldrelid = relid;
		oldnspid = nspid;
	}

	RangeVarAdjustRelationPersistence(relation, nspid);
	if (existing_relation_id != NULL)
		*existing_relation_id = relid;
	return nspid;
}