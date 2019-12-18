#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int16 ;
struct TYPE_25__ {int /*<<< orphan*/  attname; int /*<<< orphan*/  attnotnull; } ;
struct TYPE_24__ {int /*<<< orphan*/  rd_att; TYPE_4__* rd_index; TYPE_2__* rd_indam; TYPE_1__* rd_rel; } ;
struct TYPE_23__ {scalar_t__ identity_type; scalar_t__ name; } ;
struct TYPE_21__ {scalar_t__* values; } ;
struct TYPE_22__ {scalar_t__ indrelid; TYPE_3__ indkey; int /*<<< orphan*/  indisvalid; int /*<<< orphan*/  indimmediate; int /*<<< orphan*/  indisunique; } ;
struct TYPE_20__ {int /*<<< orphan*/  amcanunique; } ;
struct TYPE_19__ {int /*<<< orphan*/  relnamespace; } ;
typedef  TYPE_5__ ReplicaIdentityStmt ;
typedef  TYPE_6__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_7__* Form_pg_attribute ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERRCODE_INVALID_COLUMN_REFERENCE ; 
 int /*<<< orphan*/  ERRCODE_UNDEFINED_OBJECT ; 
 int /*<<< orphan*/  ERRCODE_WRONG_OBJECT_TYPE ; 
 int /*<<< orphan*/  ERROR ; 
 int IndexRelationGetNumberOfKeyAttributes (TYPE_6__*) ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ NIL ; 
 scalar_t__ NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ REPLICA_IDENTITY_DEFAULT ; 
 scalar_t__ REPLICA_IDENTITY_FULL ; 
 scalar_t__ REPLICA_IDENTITY_INDEX ; 
 scalar_t__ REPLICA_IDENTITY_NOTHING ; 
 scalar_t__ RelationGetIndexExpressions (TYPE_6__*) ; 
 scalar_t__ RelationGetIndexPredicate (TYPE_6__*) ; 
 scalar_t__ RelationGetRelationName (TYPE_6__*) ; 
 scalar_t__ RelationGetRelid (TYPE_6__*) ; 
 int /*<<< orphan*/  ShareLock ; 
 TYPE_7__* TupleDescAttr (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  get_relname_relid (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_close (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* index_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  relation_mark_replica_identity (TYPE_6__*,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ATExecReplicaIdentity(Relation rel, ReplicaIdentityStmt *stmt, LOCKMODE lockmode)
{
	Oid			indexOid;
	Relation	indexRel;
	int			key;

	if (stmt->identity_type == REPLICA_IDENTITY_DEFAULT)
	{
		relation_mark_replica_identity(rel, stmt->identity_type, InvalidOid, true);
		return;
	}
	else if (stmt->identity_type == REPLICA_IDENTITY_FULL)
	{
		relation_mark_replica_identity(rel, stmt->identity_type, InvalidOid, true);
		return;
	}
	else if (stmt->identity_type == REPLICA_IDENTITY_NOTHING)
	{
		relation_mark_replica_identity(rel, stmt->identity_type, InvalidOid, true);
		return;
	}
	else if (stmt->identity_type == REPLICA_IDENTITY_INDEX)
	{
		 /* fallthrough */ ;
	}
	else
		elog(ERROR, "unexpected identity type %u", stmt->identity_type);


	/* Check that the index exists */
	indexOid = get_relname_relid(stmt->name, rel->rd_rel->relnamespace);
	if (!OidIsValid(indexOid))
		ereport(ERROR,
				(errcode(ERRCODE_UNDEFINED_OBJECT),
				 errmsg("index \"%s\" for table \"%s\" does not exist",
						stmt->name, RelationGetRelationName(rel))));

	indexRel = index_open(indexOid, ShareLock);

	/* Check that the index is on the relation we're altering. */
	if (indexRel->rd_index == NULL ||
		indexRel->rd_index->indrelid != RelationGetRelid(rel))
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("\"%s\" is not an index for table \"%s\"",
						RelationGetRelationName(indexRel),
						RelationGetRelationName(rel))));
	/* The AM must support uniqueness, and the index must in fact be unique. */
	if (!indexRel->rd_indam->amcanunique ||
		!indexRel->rd_index->indisunique)
		ereport(ERROR,
				(errcode(ERRCODE_WRONG_OBJECT_TYPE),
				 errmsg("cannot use non-unique index \"%s\" as replica identity",
						RelationGetRelationName(indexRel))));
	/* Deferred indexes are not guaranteed to be always unique. */
	if (!indexRel->rd_index->indimmediate)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot use non-immediate index \"%s\" as replica identity",
						RelationGetRelationName(indexRel))));
	/* Expression indexes aren't supported. */
	if (RelationGetIndexExpressions(indexRel) != NIL)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot use expression index \"%s\" as replica identity",
						RelationGetRelationName(indexRel))));
	/* Predicate indexes aren't supported. */
	if (RelationGetIndexPredicate(indexRel) != NIL)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot use partial index \"%s\" as replica identity",
						RelationGetRelationName(indexRel))));
	/* And neither are invalid indexes. */
	if (!indexRel->rd_index->indisvalid)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot use invalid index \"%s\" as replica identity",
						RelationGetRelationName(indexRel))));

	/* Check index for nullable columns. */
	for (key = 0; key < IndexRelationGetNumberOfKeyAttributes(indexRel); key++)
	{
		int16		attno = indexRel->rd_index->indkey.values[key];
		Form_pg_attribute attr;

		/*
		 * Reject any other system columns.  (Going forward, we'll disallow
		 * indexes containing such columns in the first place, but they might
		 * exist in older branches.)
		 */
		if (attno <= 0)
			ereport(ERROR,
					(errcode(ERRCODE_INVALID_COLUMN_REFERENCE),
					 errmsg("index \"%s\" cannot be used as replica identity because column %d is a system column",
							RelationGetRelationName(indexRel), attno)));

		attr = TupleDescAttr(rel->rd_att, attno - 1);
		if (!attr->attnotnull)
			ereport(ERROR,
					(errcode(ERRCODE_WRONG_OBJECT_TYPE),
					 errmsg("index \"%s\" cannot be used as replica identity because column \"%s\" is nullable",
							RelationGetRelationName(indexRel),
							NameStr(attr->attname))));
	}

	/* This index is suitable for use as a replica identity. Mark it. */
	relation_mark_replica_identity(rel, stmt->identity_type, indexOid, true);

	index_close(indexRel, NoLock);
}