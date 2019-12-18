#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int32 ;
struct TYPE_14__ {int /*<<< orphan*/  relname; } ;
struct TYPE_13__ {int /*<<< orphan*/  newschema; TYPE_8__* relation; scalar_t__ missing_ok; } ;
struct TYPE_12__ {TYPE_1__* rd_rel; } ;
struct TYPE_11__ {scalar_t__ relkind; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  RangeVar ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddresses ;
typedef  int /*<<< orphan*/  ObjectAddress ;
typedef  TYPE_3__ AlterObjectSchemaStmt ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AlterTableNamespaceInternal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CheckSetNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEPENDENCY_AUTO ; 
 int /*<<< orphan*/  DEPENDENCY_INTERNAL ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InvalidObjectAddress ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  ObjectAddressSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_SEQUENCE ; 
 int /*<<< orphan*/  RVR_MISSING_OK ; 
 int /*<<< orphan*/  RangeVarCallbackForAlterRelation ; 
 int /*<<< orphan*/  RangeVarGetAndCheckCreationNamespace (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RangeVarGetRelidExtended (TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  RelationGetNamespace (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errdetail (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,...) ; 
 int /*<<< orphan*/  free_object_addresses (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * makeRangeVar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * new_object_addresses () ; 
 int /*<<< orphan*/  relation_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* relation_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sequenceIsOwned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ObjectAddress
AlterTableNamespace(AlterObjectSchemaStmt *stmt, Oid *oldschema)
{
	Relation	rel;
	Oid			relid;
	Oid			oldNspOid;
	Oid			nspOid;
	RangeVar   *newrv;
	ObjectAddresses *objsMoved;
	ObjectAddress myself;

	relid = RangeVarGetRelidExtended(stmt->relation, AccessExclusiveLock,
									 stmt->missing_ok ? RVR_MISSING_OK : 0,
									 RangeVarCallbackForAlterRelation,
									 (void *) stmt);

	if (!OidIsValid(relid))
	{
		ereport(NOTICE,
				(errmsg("relation \"%s\" does not exist, skipping",
						stmt->relation->relname)));
		return InvalidObjectAddress;
	}

	rel = relation_open(relid, NoLock);

	oldNspOid = RelationGetNamespace(rel);

	/* If it's an owned sequence, disallow moving it by itself. */
	if (rel->rd_rel->relkind == RELKIND_SEQUENCE)
	{
		Oid			tableId;
		int32		colId;

		if (sequenceIsOwned(relid, DEPENDENCY_AUTO, &tableId, &colId) ||
			sequenceIsOwned(relid, DEPENDENCY_INTERNAL, &tableId, &colId))
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot move an owned sequence into another schema"),
					 errdetail("Sequence \"%s\" is linked to table \"%s\".",
							   RelationGetRelationName(rel),
							   get_rel_name(tableId))));
	}

	/* Get and lock schema OID and check its permissions. */
	newrv = makeRangeVar(stmt->newschema, RelationGetRelationName(rel), -1);
	nspOid = RangeVarGetAndCheckCreationNamespace(newrv, NoLock, NULL);

	/* common checks on switching namespaces */
	CheckSetNamespace(oldNspOid, nspOid);

	objsMoved = new_object_addresses();
	AlterTableNamespaceInternal(rel, oldNspOid, nspOid, objsMoved);
	free_object_addresses(objsMoved);

	ObjectAddressSet(myself, RelationRelationId, relid);

	if (oldschema)
		*oldschema = oldNspOid;

	/* close rel, but keep lock until commit */
	relation_close(rel, NoLock);

	return myself;
}