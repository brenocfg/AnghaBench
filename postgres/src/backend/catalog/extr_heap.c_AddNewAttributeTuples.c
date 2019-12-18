#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* TupleDesc ;
struct TYPE_14__ {int attstattarget; scalar_t__ atttypid; scalar_t__ attcollation; void* attrelid; } ;
struct TYPE_13__ {scalar_t__ objectId; int objectSubId; int /*<<< orphan*/  classId; } ;
struct TYPE_12__ {int natts; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  void* Oid ;
typedef  TYPE_2__ ObjectAddress ;
typedef  TYPE_3__* Form_pg_attribute ;
typedef  TYPE_3__ FormData_pg_attribute ;
typedef  int /*<<< orphan*/  CatalogIndexState ;

/* Variables and functions */
 int /*<<< orphan*/  AttributeRelationId ; 
 int /*<<< orphan*/  CatalogCloseIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CatalogOpenIndexes (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CollationRelationId ; 
 scalar_t__ DEFAULT_COLLATION_OID ; 
 int /*<<< orphan*/  DEPENDENCY_NORMAL ; 
 int /*<<< orphan*/  InsertPgAttributeTuple (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ OidIsValid (scalar_t__) ; 
 char RELKIND_COMPOSITE_TYPE ; 
 char RELKIND_VIEW ; 
 int /*<<< orphan*/  RelationRelationId ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 int /*<<< orphan*/ * SysAtt ; 
 TYPE_3__* TupleDescAttr (TYPE_1__*,int) ; 
 int /*<<< orphan*/  TypeRelationId ; 
 scalar_t__ lengthof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  recordDependencyOn (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
AddNewAttributeTuples(Oid new_rel_oid,
					  TupleDesc tupdesc,
					  char relkind)
{
	Form_pg_attribute attr;
	int			i;
	Relation	rel;
	CatalogIndexState indstate;
	int			natts = tupdesc->natts;
	ObjectAddress myself,
				referenced;

	/*
	 * open pg_attribute and its indexes.
	 */
	rel = table_open(AttributeRelationId, RowExclusiveLock);

	indstate = CatalogOpenIndexes(rel);

	/*
	 * First we add the user attributes.  This is also a convenient place to
	 * add dependencies on their datatypes and collations.
	 */
	for (i = 0; i < natts; i++)
	{
		attr = TupleDescAttr(tupdesc, i);
		/* Fill in the correct relation OID */
		attr->attrelid = new_rel_oid;
		/* Make sure this is OK, too */
		attr->attstattarget = -1;

		InsertPgAttributeTuple(rel, attr, indstate);

		/* Add dependency info */
		myself.classId = RelationRelationId;
		myself.objectId = new_rel_oid;
		myself.objectSubId = i + 1;
		referenced.classId = TypeRelationId;
		referenced.objectId = attr->atttypid;
		referenced.objectSubId = 0;
		recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);

		/* The default collation is pinned, so don't bother recording it */
		if (OidIsValid(attr->attcollation) &&
			attr->attcollation != DEFAULT_COLLATION_OID)
		{
			referenced.classId = CollationRelationId;
			referenced.objectId = attr->attcollation;
			referenced.objectSubId = 0;
			recordDependencyOn(&myself, &referenced, DEPENDENCY_NORMAL);
		}
	}

	/*
	 * Next we add the system attributes.  Skip OID if rel has no OIDs. Skip
	 * all for a view or type relation.  We don't bother with making datatype
	 * dependencies here, since presumably all these types are pinned.
	 */
	if (relkind != RELKIND_VIEW && relkind != RELKIND_COMPOSITE_TYPE)
	{
		for (i = 0; i < (int) lengthof(SysAtt); i++)
		{
			FormData_pg_attribute attStruct;

			memcpy(&attStruct, SysAtt[i], sizeof(FormData_pg_attribute));

			/* Fill in the correct relation OID in the copied tuple */
			attStruct.attrelid = new_rel_oid;

			InsertPgAttributeTuple(rel, &attStruct, indstate);
		}
	}

	/*
	 * clean up
	 */
	CatalogCloseIndexes(indstate);

	table_close(rel, RowExclusiveLock);
}