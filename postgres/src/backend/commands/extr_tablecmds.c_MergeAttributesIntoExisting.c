#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* TupleDesc ;
struct TYPE_26__ {scalar_t__ atttypid; scalar_t__ atttypmod; scalar_t__ attcollation; int attinhcount; int attislocal; scalar_t__ attnotnull; scalar_t__ attisdropped; int /*<<< orphan*/  attname; } ;
struct TYPE_25__ {int /*<<< orphan*/  t_self; } ;
struct TYPE_24__ {TYPE_1__* rd_rel; } ;
struct TYPE_23__ {int natts; } ;
struct TYPE_22__ {scalar_t__ relkind; } ;
typedef  TYPE_3__* Relation ;
typedef  TYPE_4__* HeapTuple ;
typedef  TYPE_5__* Form_pg_attribute ;
typedef  int AttrNumber ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  AttributeRelationId ; 
 int /*<<< orphan*/  CatalogTupleUpdate (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ERRCODE_COLLATION_MISMATCH ; 
 int /*<<< orphan*/  ERRCODE_DATATYPE_MISMATCH ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  GETSTRUCT (TYPE_4__*) ; 
 scalar_t__ HeapTupleIsValid (TYPE_4__*) ; 
 char* NameStr (int /*<<< orphan*/ ) ; 
 scalar_t__ RELKIND_PARTITIONED_TABLE ; 
 TYPE_2__* RelationGetDescr (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelationName (TYPE_3__*) ; 
 int /*<<< orphan*/  RelationGetRelid (TYPE_3__*) ; 
 int /*<<< orphan*/  RowExclusiveLock ; 
 TYPE_4__* SearchSysCacheCopyAttName (int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* TupleDescAttr (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char*,...) ; 
 int /*<<< orphan*/  heap_freetuple (TYPE_4__*) ; 
 int /*<<< orphan*/  table_close (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* table_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
MergeAttributesIntoExisting(Relation child_rel, Relation parent_rel)
{
	Relation	attrrel;
	AttrNumber	parent_attno;
	int			parent_natts;
	TupleDesc	tupleDesc;
	HeapTuple	tuple;
	bool		child_is_partition = false;

	attrrel = table_open(AttributeRelationId, RowExclusiveLock);

	tupleDesc = RelationGetDescr(parent_rel);
	parent_natts = tupleDesc->natts;

	/* If parent_rel is a partitioned table, child_rel must be a partition */
	if (parent_rel->rd_rel->relkind == RELKIND_PARTITIONED_TABLE)
		child_is_partition = true;

	for (parent_attno = 1; parent_attno <= parent_natts; parent_attno++)
	{
		Form_pg_attribute attribute = TupleDescAttr(tupleDesc,
													parent_attno - 1);
		char	   *attributeName = NameStr(attribute->attname);

		/* Ignore dropped columns in the parent. */
		if (attribute->attisdropped)
			continue;

		/* Find same column in child (matching on column name). */
		tuple = SearchSysCacheCopyAttName(RelationGetRelid(child_rel),
										  attributeName);
		if (HeapTupleIsValid(tuple))
		{
			/* Check they are same type, typmod, and collation */
			Form_pg_attribute childatt = (Form_pg_attribute) GETSTRUCT(tuple);

			if (attribute->atttypid != childatt->atttypid ||
				attribute->atttypmod != childatt->atttypmod)
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("child table \"%s\" has different type for column \"%s\"",
								RelationGetRelationName(child_rel),
								attributeName)));

			if (attribute->attcollation != childatt->attcollation)
				ereport(ERROR,
						(errcode(ERRCODE_COLLATION_MISMATCH),
						 errmsg("child table \"%s\" has different collation for column \"%s\"",
								RelationGetRelationName(child_rel),
								attributeName)));

			/*
			 * Check child doesn't discard NOT NULL property.  (Other
			 * constraints are checked elsewhere.)
			 */
			if (attribute->attnotnull && !childatt->attnotnull)
				ereport(ERROR,
						(errcode(ERRCODE_DATATYPE_MISMATCH),
						 errmsg("column \"%s\" in child table must be marked NOT NULL",
								attributeName)));

			/*
			 * OK, bump the child column's inheritance count.  (If we fail
			 * later on, this change will just roll back.)
			 */
			childatt->attinhcount++;

			/*
			 * In case of partitions, we must enforce that value of attislocal
			 * is same in all partitions. (Note: there are only inherited
			 * attributes in partitions)
			 */
			if (child_is_partition)
			{
				Assert(childatt->attinhcount == 1);
				childatt->attislocal = false;
			}

			CatalogTupleUpdate(attrrel, &tuple->t_self, tuple);
			heap_freetuple(tuple);
		}
		else
		{
			ereport(ERROR,
					(errcode(ERRCODE_DATATYPE_MISMATCH),
					 errmsg("child table is missing column \"%s\"",
							attributeName)));
		}
	}

	table_close(attrrel, RowExclusiveLock);
}