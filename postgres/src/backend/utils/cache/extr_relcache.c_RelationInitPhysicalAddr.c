#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ reltablespace; scalar_t__ relfilenode; } ;
struct TYPE_10__ {scalar_t__ spcNode; scalar_t__ relNode; int /*<<< orphan*/  dbNode; } ;
struct TYPE_11__ {int /*<<< orphan*/  rd_id; TYPE_2__ rd_node; TYPE_1__* rd_rel; } ;
struct TYPE_9__ {scalar_t__ reltablespace; int /*<<< orphan*/  relisshared; scalar_t__ relfilenode; int /*<<< orphan*/  relkind; } ;
typedef  TYPE_3__* Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_4__* Form_pg_class ;

/* Variables and functions */
 scalar_t__ ClassOidIndexId ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 scalar_t__ GLOBALTABLESPACE_OID ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 scalar_t__ HistoricSnapshotActive () ; 
 int /*<<< orphan*/  InvalidOid ; 
 scalar_t__ IsTransactionState () ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 scalar_t__ MyDatabaseTableSpace ; 
 int /*<<< orphan*/  OidIsValid (scalar_t__) ; 
 int /*<<< orphan*/  RELKIND_HAS_STORAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 scalar_t__ RelationGetRelid (TYPE_3__*) ; 
 scalar_t__ RelationIsAccessibleInLogicalDecoding (TYPE_3__*) ; 
 scalar_t__ RelationMapOidToFilenode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ScanPgRelation (scalar_t__,int,int) ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  heap_freetuple (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
RelationInitPhysicalAddr(Relation relation)
{
	/* these relations kinds never have storage */
	if (!RELKIND_HAS_STORAGE(relation->rd_rel->relkind))
		return;

	if (relation->rd_rel->reltablespace)
		relation->rd_node.spcNode = relation->rd_rel->reltablespace;
	else
		relation->rd_node.spcNode = MyDatabaseTableSpace;
	if (relation->rd_node.spcNode == GLOBALTABLESPACE_OID)
		relation->rd_node.dbNode = InvalidOid;
	else
		relation->rd_node.dbNode = MyDatabaseId;

	if (relation->rd_rel->relfilenode)
	{
		/*
		 * Even if we are using a decoding snapshot that doesn't represent the
		 * current state of the catalog we need to make sure the filenode
		 * points to the current file since the older file will be gone (or
		 * truncated). The new file will still contain older rows so lookups
		 * in them will work correctly. This wouldn't work correctly if
		 * rewrites were allowed to change the schema in an incompatible way,
		 * but those are prevented both on catalog tables and on user tables
		 * declared as additional catalog tables.
		 */
		if (HistoricSnapshotActive()
			&& RelationIsAccessibleInLogicalDecoding(relation)
			&& IsTransactionState())
		{
			HeapTuple	phys_tuple;
			Form_pg_class physrel;

			phys_tuple = ScanPgRelation(RelationGetRelid(relation),
										RelationGetRelid(relation) != ClassOidIndexId,
										true);
			if (!HeapTupleIsValid(phys_tuple))
				elog(ERROR, "could not find pg_class entry for %u",
					 RelationGetRelid(relation));
			physrel = (Form_pg_class) GETSTRUCT(phys_tuple);

			relation->rd_rel->reltablespace = physrel->reltablespace;
			relation->rd_rel->relfilenode = physrel->relfilenode;
			heap_freetuple(phys_tuple);
		}

		relation->rd_node.relNode = relation->rd_rel->relfilenode;
	}
	else
	{
		/* Consult the relation mapper */
		relation->rd_node.relNode =
			RelationMapOidToFilenode(relation->rd_id,
									 relation->rd_rel->relisshared);
		if (!OidIsValid(relation->rd_node.relNode))
			elog(ERROR, "could not find relation mapping for relation \"%s\", OID %u",
				 RelationGetRelationName(relation), relation->rd_id);
	}
}