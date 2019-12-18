#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* rd_rel; } ;
struct TYPE_12__ {scalar_t__ relkind; int /*<<< orphan*/  reltype; } ;
typedef  TYPE_2__* Relation ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  ObjectAddresses ;

/* Variables and functions */
 int /*<<< orphan*/  AccessExclusiveLock ; 
 int /*<<< orphan*/  AlterConstraintNamespaces (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AlterIndexNamespaces (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AlterRelationNamespaceInternal (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AlterSeqNamespaces (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AlterTypeNamespaceInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_MATVIEW ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 scalar_t__ RELKIND_RELATION ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_2__*) ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/  table_close (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
AlterTableNamespaceInternal(Relation rel, Oid oldNspOid, Oid nspOid,
							ObjectAddresses *objsMoved)
{
	Relation	classRel;

	Assert(objsMoved != NULL);

	/* OK, modify the pg_class row and pg_depend entry */
	classRel = table_open(RelationRelationId, RowExclusiveLock);

	AlterRelationNamespaceInternal(classRel, RelationGetRelid(rel), oldNspOid,
								   nspOid, true, objsMoved);

	/* Fix the table's row type too */
	AlterTypeNamespaceInternal(rel->rd_rel->reltype,
							   nspOid, false, false, objsMoved);

	/* Fix other dependent stuff */
	if (rel->rd_rel->relkind == RELKIND_RELATION ||
		rel->rd_rel->relkind == RELKIND_MATVIEW ||
		rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
	{
		AlterIndexNamespaces(classRel, rel, oldNspOid, nspOid, objsMoved);
		AlterSeqNamespaces(classRel, rel, oldNspOid, nspOid,
						   objsMoved, AccessExclusiveLock);
		AlterConstraintNamespaces(RelationGetRelid(rel), oldNspOid, nspOid,
								  false, objsMoved);
	}

	table_close(classRel, RowExclusiveLock);
}